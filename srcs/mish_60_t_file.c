/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_60_t_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/21 14:47:58 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

// tf->line est peut etre inutile
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
	tf->line = ft_strempty(NULL);
	return (tf);
}

void	t_file_free(t_file **tf)
{
	if (*tf)
	{
		if ((*tf)->next)
			t_file_free(&((*tf)->next));
		t_file_del(tf);
	}
}

void	t_file_del(t_file	**tf)
{
	if (*tf)
	{
		if ((*tf)->path)
			free((*tf)->path);
		if ((*tf)->line)
			free((*tf)->line);
		free(*tf);
		*tf = NULL; //a tester
	}
}

void	t_process_iofiles_error(t_process *p, int en, char *path, int *err)
{
	mish_error_print(en, path);	
	if (p)
		t_process_cmd_setempty(p);
	// mish_p_iofiles_close(p->mish);
	// ou
	t_process_iofile_add(p, "error", tf_ifile_rdonly);
	t_process_iofile_add(p, "error", tf_ofile_creat);
	*err = en;
	// set exit var
}
