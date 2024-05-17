/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_63_p_files_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/17 15:38:02 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

static void	heredoc_ctrld_message(int i, char *path)
{
	char	*str;

	str = ft_itoa(i);
	if (str == NULL)
		return;
	write(2, "minishell: warning: here-document at line ", 43);
	write(2, str, ft_strlen(str));
	write(2, " delimited by EOF (wanted '", 28);
	write(2, path, ft_strlen(path));
	write(2, "')\n", 4);
	free(str);
}

static void	t_file_line_heredoc(t_file *tfile, t_mish *mish)
{
	char	*line;
	int		i;

	i = 0;
	while (tfile->line && mish_continue(mish))
	{
		line = readline(">");
		if (!line)
		{
			heredoc_ctrld_message(i, tfile->path);
			break;
		}
		if (!ft_strcmp(line, tfile->path)) //|| ft_strcmp(line, "^C"))
		{
			free(line);
			break;
		}
		line = mish_substitute_str(mish, NULL, line);
		tfile->line = ft_strjointo(tfile->line, line);
		tfile->line = ft_strjointo(tfile->line, "\n");
		free(line);
		i++;
	}
	if (tfile->line == NULL)
		mish_error_add(mish, err_malloc, errno, "malloc in t_file_heredoc");
}

void	t_file_heredoc(t_file *tfile, int openfile, t_mish *mish)
{	
	t_file_line_heredoc(tfile, mish);
	if (openfile == 0)
		return ;
	tfile->path = ft_strdupfree(tfile->path, ".heredoc");
	while (access(tfile->path, F_OK) == 0)
	{
		free(tfile->path);
		tfile->path = ft_strjointoleft(ft_itoa(randint()), ".heredoc");
	}
	tfile->fd = open(tfile->path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (tfile->fd == -1)
		mish_error_print(2, tfile->path);
	else
	{
		if (write(tfile->fd, tfile->line, ft_strlen(tfile->line)) == -1)
		{
			mish_error_print(errno, tfile->path);
			close_reset_fd(&(tfile->fd));
		}
		else
		{
			close(tfile->fd);
			tfile->fd = open(tfile->path, O_RDONLY | O_CREAT | O_APPEND, 0644);
		}
	}
}
