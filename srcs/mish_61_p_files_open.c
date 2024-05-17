/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_61_p_files_open.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/17 17:52:35 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	t_process_open_infiles(t_process *p, t_tfile_type type)
{
	t_file	*tfile;

	tfile = p->infiles;
	while (tfile && mish_continue(p->mish))
	{
		if (tfile->type == tf_ifile_rdonly && type == tf_ifile_rdonly)
		{
			tfile->fd = open(tfile->path, O_RDONLY);
			if (tfile->fd == -1)
				t_process_iofiles_error(p, errno, tfile->path);
			else if (tfile->next)
				close_reset_fd(&(tfile->fd));
		}
		else if (tfile->type == tf_ifile_heredoc && type == tf_ifile_heredoc)
		{
			if (tfile->next)
				t_file_heredoc(tfile, 0, p->mish);
			else
				t_file_heredoc(tfile, 1, p->mish);
		}
		tfile = tfile->next;
	}
}

void	t_process_open_outfiles(t_process *p)
{
	t_file	*tfile;

	tfile = p->outfiles;
	while (tfile)
	{
		if (tfile->type == tf_ofile_creat)
		{
			tfile->fd = open(tfile->path, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (tfile->fd == -1)
				t_process_iofiles_error(p, errno, tfile->path);
			else if (tfile->next)
				close_reset_fd(&(tfile->fd));
		}
		else if (tfile->type == tf_ofile_append)
		{
			tfile->fd = open(tfile->path, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (tfile->fd == -1)
				t_process_iofiles_error(p, errno, tfile->path);
			else if (tfile->next)
				close_reset_fd(&(tfile->fd));
		}
		tfile = tfile->next;
	}
}

void	t_process_open_iofiles(t_process *process)
{
	t_process_open_infiles(process, tf_ifile_heredoc);
	t_process_open_infiles(process, tf_ifile_rdonly);
	t_process_open_outfiles(process);
}
