/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_51_process_iofiles_01.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/14 11:47:21 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_file	*t_process_line_to_file(t_process *p, char *line)
{
	t_file			*file;
	char			*path;
	t_tfile_type	file_type;

	path = t_file_line_get_path(line);
	file_type = t_file_line_get_type(line);
	file = t_process_add_file(p, path, file_type);
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

t_file	*t_process_add_file(t_process *p, char *path, t_tfile_type type)
{
	t_file	*new;
	t_file	*current;

	// printf("path = %s\tftype = %d\n", path, type); /////
	if (type == tf_ifile_rdonly || type == tf_ifile_heredoc)
		current = p->infiles;
	else if (type != tf_none)
		current = p->outfiles;
	else
		return (NULL);
	new = t_file_new(p->mish, path, type);
/*	if (new)
	{
		if (type == tf_ifile_rdonly || type == tf_ifile_heredoc)
			t_file_add_back_rec(&(*p)->infiles, new);
		else if (type != tf_none)
			t_file_add_back_rec(&(*p)->outfiles, new);
		else
		{
			free(new->path);
			free(new);
			return (NULL);
		}
	}
*/	
	while (current)
		current = current->next;
	current = new;
	return (new);
}
