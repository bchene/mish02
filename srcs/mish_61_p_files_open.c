/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_61_p_files_open.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/21 17:08:04 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

/*
revoir l ouverture
faire l ensemble des here docs
puis
faire l enseble des ouverture tant que ca marche sinon exit.
faire la boucle des ouverture dans iofileopen et traiter les sorties
*/

void	mish_open_iofiles(t_mish *mish)
{
	int	err;
	int	i;

	err = 0;
	i = -1;
	while (++i < mish->nb)
		t_process_open_heredoc(mish->p + i, 1);
	i = -1;
	while (++i < mish->nb)
		t_process_open_iofiles(mish->p + i, &err);		
	// i = -1;
	// while (++i < mish->nb)
	// 	t_process_iofile_print(mish->p + i);	
}

void	t_process_open_heredoc(t_process *p, int openfile)
{
	t_file	*tfile;

	tfile = p->iofiles;
	while (tfile && mish_continue(p->mish))
	{
		if (tfile->type == tf_ifile_heredoc)
		{

			if (openfile == 1 && tfile == t_process_iofile_get(p, 0))
				t_file_heredoc(tfile, 1, p->mish);
			else
				t_file_heredoc(tfile, 0, p->mish);
		}
		tfile = tfile->next;
	}
}

void	t_process_open_iofiles(t_process *p, int *err)
{
	t_file	*tfile;

	tfile = p->iofiles;
	while (tfile && mish_continue(p->mish) && (*err == 0))
	{
		if (tfile->type == tf_ifile_rdonly)
			tfile->fd = open(tfile->path, O_RDONLY);
		else if (tfile->type == tf_ofile_creat)
			tfile->fd = open(tfile->path, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (tfile->type == tf_ofile_append)
			tfile->fd = open(tfile->path, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (tfile->fd == -1)
			t_process_iofiles_error(p, errno, tfile->path, err);
		else if (!(tfile == t_process_iofile_get(p, 0) || \
		tfile == t_process_iofile_get(p, 1)))
			close_reset_fd(&(tfile->fd));
		tfile = tfile->next;
	}
}
/*
void	t_process_open_rdonly(t_process *p, int *err)
{
	t_file	*tfile;

	tfile = p->infiles;
	while (tfile && mish_continue(p->mish) && (*err == 0))
	{
		if (tfile->type == tf_ifile_rdonly)
		{
			tfile->fd = open(tfile->path, O_RDONLY);
			if (tfile->fd == -1)
				t_process_iofiles_error(p, errno, tfile->path, err);
			else if (tfile->next)
				close_reset_fd(&(tfile->fd));
		}
		tfile = tfile->next;
	}
}
*/

/*
void	t_process_open_creat(t_process *p, int *err)
{
	t_file	*tfile;

	tfile = p->outfiles;
	while (tfile)
	{
		if (tfile->type == tf_ofile_creat && (*err == 0))
		{
			tfile->fd = open(tfile->path, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (tfile->fd == -1)
				t_process_iofiles_error(p, errno, tfile->path, err);
			else if (tfile->next)
				close_reset_fd(&(tfile->fd));
		}
		tfile = tfile->next;
	}
}
*/

/*
void	t_process_open_append(t_process *p, int *err)
{
	t_file	*tfile;

	tfile = p->outfiles;
	while (tfile)
	{
		if (tfile->type == tf_ofile_append && (*err == 0))
		{
			tfile->fd = open(tfile->path, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (tfile->fd == -1)
				t_process_iofiles_error(p, errno, tfile->path, err);
			else if (tfile->next)
				close_reset_fd(&(tfile->fd));
		}
		tfile = tfile->next;
	}	
}
*/

/*
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
*/

/*	i = -1;
	while (++i < mish->nb)
	{
		t_process_open_infiles((mish->p) + i, tf_ifile_rdonly);
		t_process_open_outfiles((mish->p) + i);
	}
	t_process_open_infiles(process, tf_ifile_rdonly);
	t_process_open_outfiles(process);
}
*/

/*
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
				t_process_iofiles_error(p, errno, tfile->path, err);
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
*/