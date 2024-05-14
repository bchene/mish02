/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_51_process_iofiles_00.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/14 11:47:07 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_file	*t_process_iofile_add(t_process *p, char *path, t_tfile_type type)
{
	t_file	*new;
	t_file	*current;

	if (type == tf_ifile_rdonly || type == tf_ifile_heredoc)
		current = p->infiles;
	else
		current = p->outfiles;
	new = t_file_new(p->mish, path, type);
	if (current == NULL)
	{
		if (type == tf_ifile_rdonly || type == tf_ifile_heredoc)
			p->infiles = new;
		else
			p->outfiles = new;
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (new);
}

/* inorout : ==0 IN - !=0 OUT */
int	t_process_iofile_get(t_process *process, int inorout)
{
	t_file	*tf;

	if (inorout == 0)
	{
		if (process == NULL || process->infiles == NULL)
			return (0);
		tf = process->infiles;
	}
	else
	{
		if (process == NULL || process->outfiles == NULL)
			return (1);
		tf = process->outfiles;
	}
	while (tf->next)
		tf = tf->next;
	return (tf->fd);
}

void	t_process_iofile_print(t_process *process)
{
	t_file	*tf;

	tf = process->infiles;
	printf("infiles = ");
	while (tf)
	{
		printf("(\"%s\", %i) ", tf->path, tf->type);
		tf = tf->next;
	}
	printf("\n");
	tf = process->outfiles;
	printf("outfiles = ");
	while (tf)
	{
		printf("(\"%s\", %i) ", tf->path, tf->type);
		tf = tf->next;
	}
	printf("\n");
}
