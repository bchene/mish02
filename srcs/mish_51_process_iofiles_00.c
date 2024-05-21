/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_51_process_iofiles_00.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/21 17:34:42 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_file	*t_process_iofile_add(t_process *p, char *path, t_tfile_type type)
{
	t_file	*new;
	t_file	*current;

	current = p->iofiles;

	new = t_file_new(p->mish, path, type);
	if (current == NULL)
		p->iofiles = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (new);
}

/* inorout : ==0 IN - ==1 OUT */
t_file	*t_process_iofile_get(t_process *process, int inorout)
{
	t_file	*tf;
	t_file	*ret;

	tf = process->iofiles;
	ret = NULL;
	while (tf)
	{
		if (inorout == 0 && (tf->type == tf_ifile_rdonly || tf->type == tf_ifile_heredoc))
			ret = tf;
		else if (inorout == 1 && (tf->type == tf_ofile_creat || tf->type == tf_ofile_append))
			ret = tf;
		tf = tf->next;
	}
	return (ret);
}

int	t_process_iofile_getfd(t_process *process, int inorout)
{
	int		ret;
	t_file	*tf;

	tf = t_process_iofile_get(process, inorout);
	if (tf == NULL)
		return (-1);
	ret = tf->fd;
	return (ret);
}

void	t_process_iofile_print(t_process *process)
{
	t_file	*tf;
	char	**ttype;

	ttype = ft_split("NONE HEREDOC RDONLY CREAT APPEND", ' ');
	if (ttype == NULL)
		return ;
	tf = process->iofiles;
	printf("iofiles = ");
	if (tf == NULL)
		printf("(null)");
	else
	{
		while (tf)
		{
			printf("(\"%s\", %s) ", tf->path, ttype[tf->type]);
			tf = tf->next;
		}
	}
	printf("\n");
	ft_freesplit(ttype);
}
