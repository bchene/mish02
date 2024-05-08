/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_62_p_files_close.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/08 17:54:37 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	t_process_close_infile(t_process *p)
{
	t_file *tfile;

	tfile = p->infiles;
	while (tfile)
	{
		if (tfile->fd > 2)
			close_reset_fd(&(tfile->fd));
		tfile = tfile->next;
	}
}

void	t_process_close_outfile(t_process *p)
{
	t_file *tfile;

	tfile = p->outfiles;
	while (tfile)
	{
		if (tfile->fd > 2)
			close_reset_fd(&(tfile->fd));
		tfile = tfile->next;
	}
}
/*
void	t_process_iofiles_closeother(t_process *p)
{
	int	i;

	i = -1;
	while (++i < p->mish->nb)
	{
		if (i != p->index)
		{
			t_process_close_infile((p->mish->p) + i);
			t_process_close_outfile((p->mish->p) + i);
		}
	}
}
*/

void	mish_p_iofiles_close(t_mish *mish)
{
	int	i;

	i = -1;
	while (++i < mish->nb)
	{
		t_process_close_infile((mish->p) + i);
		t_process_close_outfile((mish->p) + i);
	}
}
