/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_60_t_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/06/03 17:20:01 by bchene           ###   ########.fr       */
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
	tf->line = ft_strempty(NULL);
	tf->limitstr = NULL;
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
		if ((*tf)->limitstr)
			free((*tf)->limitstr);
		if ((*tf)->fd > 2) //test
			close_reset_fd(&(*tf)->fd); //test
		free(*tf);
		*tf = NULL;
	}
}

int	t_process_iofiles_error(t_process *p, int en, char *path)
{
	char	*str;

	if (p->exitstatus == 0)
	{
		p->exitstatus = 1;
		str = ft_strjoinva("minishell :", path, ": ", strerror(en), "\n", NULL);
		write(2, str, ft_strlen(str));
		free(str);
	}
	if (p)
		t_process_cmd_setempty(p, "iofile_error");
	p->infile = t_process_iofile_add(p, "error", tf_ifile_rdonly);
	p->outfile = t_process_iofile_add(p, "error", tf_ofile_creat);
	return (p->exitstatus);
}

void	mish_error_print(int en, char *str)
{
	write(2, "minishell: ", 11);
	if (str)
	{
		write(2, str, ft_strlen(str));
		if (ft_strlen(strerror(en)))
			write(2, " :", 2);
	}
	if (ft_strlen(strerror(en)))
		write(2, strerror(en), ft_strlen(strerror(en)));
	write(2, "\n", 1);
}
