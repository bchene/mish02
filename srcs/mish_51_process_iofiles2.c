/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_51_process_iofiles2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/06/05 15:08:10 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_file	*t_process_line_to_file(t_process *p, char *line)
{
	t_file			*file;
	char			*path;
	char			**tmp;
	t_tfile_type	file_type;
	int				expand;

	file = NULL;
	path = t_file_line_get_path(line);
	file_type = t_file_line_get_type(line);
	tmp = ft_calloc(2, sizeof(char *));
	tmp[0] = ft_strdup(path);
	if (file_type == tf_ifile_heredoc
		&& (ft_strchr(path, '\'') || ft_strchr(path, '\"')))
		expand = 0;
	else
		expand = 1;
	if (tmp && !mish_remove_quotes(p->mish, tmp))
	{
		file = t_process_iofile_add(p, tmp[0], file_type);
		ft_freesplit(tmp);
	}
	if (file)
		file->expandhd = expand;
	return (file);
}

void	t_file_add_back_rec(t_file **lst, t_file *new)
{
	if (lst)
	{
		if (!(*lst))
			*lst = new;
		else
			t_file_add_back_rec(&(*lst)->next, new);
	}
}
