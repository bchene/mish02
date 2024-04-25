/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_fill_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:43:45 by locharve          #+#    #+#             */
/*   Updated: 2024/04/25 17:10:05 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

/**/
/* adapter avec t_file */

void	file_add_back(t_file **lst, t_file *new)
{
	if (lst)
	{
		if (!(*lst))
			*lst = new;
		else
			file_add_back(&(*lst)->next, new);
	}
}

static char	**strtab_get_io_files(char **split)
{
	char	**io_files;
	int		count;
	int		i;
	int		j;

	count = 0;
	i = -1;
	while (split[++i])
		if (is_in_str("<>", split[i][0]))
			count++;
	io_files = ft_calloc(count + 1, sizeof(char *)); // malloc
	if (io_files)
	{
		i = -1;
		j = 0;
		while (split[++i])
			if (is_in_str("<>", split[i][0]))
			{
				io_files[j] = split[i];
				j++;
			}
	}
	return (io_files);
}

static void	process_fill_io_files(t_process *p, char **split)
{
	t_file	*tmp;
	int		i;
	int		count;

	count = ft_splitsize(split);
	i = 0;
	while (i < count)
	{
		tmp = ft_calloc(1, sizeof(t_file));
		if (tmp)
		{
			tmp->line = split[i];
			if (tmp->line[0] == '<')
				file_add_back(&p->infiles, tmp);
			else if (tmp->line[0] == '>')
				file_add_back(&p->outfiles, tmp);
		}
		i++;
	}
}

static void	process_fill_av(t_process *p, char **split)
{
	char	**av;
	int		count;
	int		i;
	int		j;

	count = 0;
	i = -1;
	while (split[++i])
		if (!is_in_str("<>", split[i][0]))
			count++;
	av = ft_calloc(count + 1, sizeof(char *)); // malloc
	if (av)
	{
		i = -1;
		j = 0;
		while (split[++i])
			if (!is_in_str("<>", split[i][0]))
			{
				av[j] = split[i];
				j++;
			}
		p->av = av;
		p->ac = count;
	}
}

static int	process_fill(t_mish *mish, t_process *p)
{
	char	**split;
	char	**io_files;
	int		ret;

	(void) mish;
	ret = 0;
	split = mish_split(p, WHITESPACES);
	if (split)
	{
		mish_substitute_vars(mish, split);
		mish_remove_quotes(mish, split);
		io_files = strtab_get_io_files(split);
		if (io_files)
		{
			process_fill_io_files(p, io_files);
			free(io_files);
			process_fill_av(p, split);
		}
		else
			ret = -1;
		free(split);
	}
	return (ret);
}

int	mish_fill_processes(t_mish *mish)
{
	int	i;
	int	tmp;

	i = 0;
	while (i < mish->nb)
	{
		tmp = process_fill(mish, &mish->p[i]);
		if (tmp)
			return (tmp);
		i++;
	}
	return (0);
}
