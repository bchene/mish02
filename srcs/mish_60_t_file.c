/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_60_t_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/14 15:03:43 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_file	*t_file_new(t_mish *mish, char *path, t_tfile_type type)
{
	t_file	*tf;

	tf = malloc(sizeof(t_file));
	if (tf == NULL)
	{
		mish_error_add(mish, err_malloc, errno, "t_file_new");
		return (NULL);
	}
	tf->fd = -1;
	tf->path = ft_strdup(path);
	tf->type = type;
	tf->next = NULL;
	return (tf);
}

void	t_file_free(t_file *tf)
{
	if (tf)
	{
		if (tf->next)
			t_file_free(tf->next);
		t_file_del(tf);
	}
}

void	t_file_del(t_file	*tf)
{
	if (tf)
		if (tf->path)
			free(tf->path);
	free(tf);
}

void	t_process_iofiles_error(t_process *p, int en, char *path)
{
	if (p->av || (p->av)[0])
		t_process_cmd_setempty(p);
	mish_error_print(en, path);
}
