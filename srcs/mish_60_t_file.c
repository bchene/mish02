/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_60_t_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/06 17:47:30 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

// ajouter des argument pour le constructeur
// mieux definir la structure
// a suivre

/*
char **unxp_token;
unxp_token = {"||", "\\", "<>", "<&", ";", "&",}
<> < > <<< <<> 
echo <      > file
*/

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
		if(tf->path)
			free(tf->path);
	free(tf);
}

// t_file		*t_process_add_file_line(t_mish *mish, char *line);
/*
t_file	*t_process_line_to_file(t_mish *mish, char *line)
{
	(void) mish;
	(void) line;
	// a faire
	//t_file	*t_file_new(t_mish *mish, char *path, t_tfile_type type)

	return (NULL);
}
*/

t_file	*t_process_add_file(t_process *p, char *path, t_tfile_type type)
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
int	t_process_get_iofd(t_process *process, int inorout)
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
	return(tf->fd);
}