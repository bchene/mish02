/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_63_p_files_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/06/05 15:01:35 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

static void	heredoc_ctrld_message(int i, char *path)
{
	char	*str;

	str = ft_itoa(i);
	if (str == NULL)
		return ;
	write(2, "minishell: warning: here-document at line ", 43);
	write(2, str, ft_strlen(str));
	write(2, " delimited by EOF (wanted '", 28);
	write(2, path, ft_strlen(path));
	write(2, "')\n", 4);
	free(str);
}

static void	t_file_readline_heredoc(t_file *tfile, t_mish *mish)
{
	char	*line;
	int		i;

	i = -1;
	while (++i >= 0 && tfile->line && mish_continue(mish))
	{
		line = readline(">");
		if (g_signal == SIGINT)
			break ;
		if (!line)
		{
			heredoc_ctrld_message(i, tfile->path);
			break ;
		}
		if (!ft_strcmp(line, tfile->path))
		{
			free(line);
			break ;
		}
		if (tfile->expandhd)
			line = mish_substitute_str(mish, NULL, line);
		tfile->line = ft_strjointo(tfile->line, line);
		tfile->line = ft_strjointo(tfile->line, "\n");
		free(line);
	}
}

static void	t_file_line_heredoc(t_file *tfile, t_mish *mish)
{
	handler_set_type(handler_heredoc);
	t_file_readline_heredoc(tfile, mish);
	if (g_signal == SIGINT)
	{
		mish_exit_status_set(mish, 130);
		mish_error_add(mish, err_hd_ctrlc, 0, "herecdoc CTRLC");
	}
	handler_set_type(handler_ignore);
	if (tfile->line == NULL)
		mish_error_add(mish, err_malloc, errno, "malloc in t_file_heredoc");
}

int	t_file_heredoc(t_file *tfile, int openfile, t_process *p)
{
	t_file_line_heredoc(tfile, p->mish);
	if (openfile == 0)
		return (0);
	tfile->path = ft_strdupfree(tfile->path, ".heredoc");
	while (access(tfile->path, F_OK) == 0)
	{
		free(tfile->path);
		tfile->path = ft_strjointoleft(ft_itoa(randint()), ".heredoc");
	}
	tfile->fd = open(tfile->path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (tfile->fd == -1)
		return (t_process_iofiles_error(p, errno, tfile->path));
	else
	{
		if (write(tfile->fd, tfile->line, ft_strlen(tfile->line)) == -1)
			return (t_process_iofiles_error(p, errno, tfile->path));
		else
		{
			close(tfile->fd);
			tfile->fd = open(tfile->path, O_RDONLY | O_CREAT | O_APPEND, 0644);
		}
	}
	return (0);
}
