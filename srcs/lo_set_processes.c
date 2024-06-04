/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_set_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:18:33 by locharve          #+#    #+#             */
/*   Updated: 2024/06/04 16:29:39 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	t_process_t_file_set(t_process *p, char **strtab)
{
	t_file	*tmp;
	int		i;

	i = 0;
	p->iofiles = NULL;
	while (p && strtab && strtab[i] && !t_error_exist(p->mish->error))
	{
		if (t_file_line_get_type(strtab[i]) != tf_ifile_heredoc)
			strtab[i] = mish_substitute_str(p->mish, NULL, strtab[i]);
		tmp = t_process_line_to_file(p, strtab[i]);
		i++;
	}
	return ;
}

void	t_process_args_set(t_process *p, char **strtab)
{
	char	*tmp;

	if (p && strtab)
	{
		strtab = mish_substitute_strtab(p->mish, &is_between_quotes, strtab);
		if (strtab)
		{
			tmp = ft_strjoin_tab(strtab, ' ');
			if (tmp)
			{
				ft_freesplit(strtab);
				strtab = mish_split(tmp, ' ');
				if (strtab && !mish_remove_quotes(p->mish, strtab))
				{
					p->av = strtab;
					p->ac = ft_splitsize(strtab);
				}
				free(tmp);
			}
		}
	}
	return ;
}

void	t_process_iofiles_args_set(t_process *p, char **iofiles, char **args)
{
	if (iofiles)
	{
		t_process_t_file_set(p, iofiles);
		ft_freesplit(iofiles);
	}
	else
		mish_error_add(p->mish, err_malloc, errno, "t_process_set");
	if (args)
		t_process_args_set(p, args);
	else
		mish_error_add(p->mish, err_malloc, errno, "t_process_set");
}

void	t_process_set(t_process *p)
{
	char	**split;
	char	**iofiles;
	char	**args;

	split = t_process_split(p, WHITESPACES);
	if (split)
	{
		iofiles = strtab_dup_if(split, t_file_line_get_type, 1);
		args = strtab_dup_if(split, t_file_line_get_type, 0);
		t_process_iofiles_args_set(p, iofiles, args);
		free(split);
	}
	else
		mish_error_add(p->mish, err_malloc, errno, "t_process_set");
	return ;
}
