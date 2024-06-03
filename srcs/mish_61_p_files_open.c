/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_61_p_files_open.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/06/03 21:59:51 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	mish_open_iofiles(t_mish *mish)
{
	int	err;
	int	i;

	err = 0;
	i = -1;
	while (++i < mish->nb && mish_continue(mish))//mish_exit_status_get(mish) != 130 
	{
		err += t_process_open_heredoc(mish->p + i, 1);
	}
	i = -1;
	while (++i < mish->nb && mish_continue(mish))
	{
		err += t_process_open_iofiles(mish->p + i);
	}
	i = -1;
	while (++i < mish->nb && mish_continue(mish))
	{
		t_process_inoutfile_get(mish->p + i);
		t_process_iofile_close_unused_fds(mish->p + i);
	}
}

//mish_continue(p->mish) &&
int	t_process_open_heredoc(t_process *p, int openfile)
{
	t_file	*tfile;
	int		err;

	err = 0;
	tfile = p->iofiles;
	while (tfile && (err == 0))
	{
		if (tfile->type == tf_ifile_heredoc)
		{
			if (openfile == 1) //dernier infd
				err += t_file_heredoc(tfile, 1, p);
			else
				err += t_file_heredoc(tfile, 0, p);
		}
		tfile = tfile->next;
	}
	return (err);
}

int	t_process_open_iofiles(t_process *p)
{
	t_file	*tfile;
	int		err;

	err = 0;
	tfile = p->iofiles;
	while (tfile && mish_continue(p->mish) && (err == 0))
	{
		if (tfile->type == tf_ifile_rdonly || tfile->type == tf_ofile_creat || \
		tfile->type == tf_ofile_append)
		{
			if (tfile->type == tf_ifile_rdonly)
				tfile->fd = open(tfile->path, O_RDONLY);
			else if (tfile->type == tf_ofile_creat)
				tfile->fd = \
				open(tfile->path, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (tfile->type == tf_ofile_append)
				tfile->fd = \
				open(tfile->path, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (tfile->fd == -1)
				err += t_process_iofiles_error(p, errno, tfile->path);
		}
		tfile = tfile->next;
	}
	return (err);
}
