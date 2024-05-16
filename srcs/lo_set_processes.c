/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_set_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:54:13 by locharve          #+#    #+#             */
/*   Updated: 2024/05/15 17:47:56 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_tfile_type	t_file_line_get_type(char *line)
{
	if (!ft_strncmp(line, "<<", 2))
		return (tf_ifile_heredoc);
	else if (!ft_strncmp(line, "<", 1))
		return (tf_ifile_rdonly);
	else if (!ft_strncmp(line, ">>", 2))
		return (tf_ofile_append);
	else if (!ft_strncmp(line, ">", 1))
		return (tf_ofile_creat);
	else
		return (tf_none);
}

char	*t_file_line_get_path(char *line)
{
	int	i;

	i = 0;
	while (line && line[i]
			&& (is_in_str(WHITESPACES, line[i])
			|| is_in_str("<>", line[i])))
		i++;
	return (&line[i]);
}

void    t_process_t_file_set(t_process *p, char **io_files)
{
	t_file	*tmp;
	int	i;

	if (io_files)
	{
		i = 0;
		while (io_files[i])
		{
			tmp = t_process_line_to_file(p, io_files[i]);
			if (tmp)
			{
				if (tmp->type == tf_ifile_rdonly || tmp->type == tf_ifile_heredoc)
					t_file_add_back_rec(&(p)->infiles, tmp);
				else if (tmp->type != tf_none)
					t_file_add_back_rec(&(p)->outfiles, tmp);
				else
				{
					free(tmp);
					return ;
				}
			}
			i++;
		}
	}
}

void	t_process_arg_set(t_process *p, char **args)
{
	if (args)
	{
		p->av = args;
		p->ac = ft_splitsize(args);
	}
}

void	t_process_set(t_process *p)
{
	char	**split;
	char	**io_files;
	char	**args;

	split = t_process_split(p, WHITESPACES); // substitution ??
	if (split)
	{
		//mish_substitute_vars(p->mish, split);
		mish_substitute_strtab(p->mish, is_between_quotes, split);
		mish_remove_quotes(p->mish, split);
		io_files = strtab_dup_if(split, t_file_line_get_type, 1);
		if (io_files)
			t_process_t_file_set(p, io_files);
		else
			mish_error_add(p->mish, err_malloc, errno, "t_process_set malloc io_files");
		args = strtab_dup_if(split, t_file_line_get_type, 0);
		if (args)
			t_process_arg_set(p, args);
		else
			mish_error_add(p->mish, err_malloc, errno, "t_process_set malloc args");
		ft_freesplit(io_files);
		free(split);
	}
	else
		mish_error_add(p->mish, err_malloc, errno, "t_process_set malloc split");
}
