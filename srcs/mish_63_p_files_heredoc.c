/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_63_p_files_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/06/03 20:56:20 by bchene           ###   ########.fr       */
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

static void	t_file_line_heredoc(t_file *tfile, t_mish *mish)
{
	char	*line;
	int		i;

	i = 0;
	handler_set_type(handler_heredoc);
	while (tfile->line && mish_continue(mish))
	{
		line = readline(">");
		if (g_signal == SIGINT)
			break;
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
		line = mish_substitute_str(mish, NULL, line);
		tfile->line = ft_strjointo(tfile->line, line);
		tfile->line = ft_strjointo(tfile->line, "\n");
		free(line);
		i++;
	}
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
	{
		tfile->fd = -1;
		return (0);
	}
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



/*
static void	child_heredoc_free(t_file *tfile, t_process *p)
{
	int exitstatus;

printf("global = %i\n", g_signal);
	exitstatus = p->exitstatus;
	if (g_signal != SIGINT && tfile->fd > 2 && tfile->line)
		if(write(tfile->fd, tfile->line, ft_strlen(tfile->line)) == -1)
			exitstatus = 2;
	if (tfile->fd > 2)
		close_reset_fd(&(tfile->fd));
	mish_free(p->mish, 0);
	if (g_signal == SIGINT)
	{
		fprintf(stderr, "exit child 130\n");//TEST
		exit (130);
	}
	fprintf(stderr, "exit child %i\n", exitstatus);
	exit (exitstatus);
}

static void	child_heredoc(t_file *tfile, t_process *p)
{
	char	*line;
	int		i;

	(p->mish)->sa.sa_sigaction = heredoc_handler; /////TEST
	i = 0;
	while (tfile->line && mish_continue(p->mish))
	{
		line = readline(">");
		if (g_signal == SIGINT)
		{
			printf("CTRL C\n");
			if (line)
				free(line);
			break ;
		}
		if (!line)
		{
			heredoc_ctrld_message(i, tfile->limitstr);
			break ;
		}
		if (!ft_strcmp(line, tfile->limitstr))
		{
			free(line);
			break ;
		}
		line = mish_substitute_str(p->mish, NULL, line);
		tfile->line = ft_strjointo(tfile->line, line);
		tfile->line = ft_strjointo(tfile->line, "\n");
		free(line);
		i++;
	}
	child_heredoc_free(tfile, p);
}

static int	t_file_open_heredoc(t_file *tfile, t_process *p)
{
	tfile->path = ft_strdupfree(tfile->path, ".heredoc");
	while (access(tfile->path, F_OK) == 0)
	{
		free(tfile->path);
		tfile->path = ft_strjointoleft(ft_itoa(randint()), ".heredoc");
	}
	tfile->fd = open(tfile->path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (tfile->fd == -1)
		return (t_process_iofiles_error(p, errno, tfile->path));
	return 0;
}

int	t_file_heredoc(t_file *tfile, int openfile, t_process *p)
{
	int	pid;
	int	status;
	int	tmp;

	tfile->limitstr = ft_strdup(tfile->path);
	if (openfile == 0)
		tfile->fd = -1;
	else if (t_file_open_heredoc(tfile, p))
		return (p->exitstatus);
	pid = fork();
	if (pid == -1)
		return (mish_error_add(p->mish, err_fork, errno, "fork in t_file_heredoc"));
	else if (pid == 0)
		child_heredoc(tfile, p);
	else //parent
	{
(p->mish)->sa.sa_sigaction = no_handler; /////TEST
		status = 0;
fprintf(stderr, "waitpid=%i exitstatus=%i\n", pid, p->exitstatus); //TEST

		while (1)
		{
            tmp = waitpid(pid, &status, 0);
			if (tmp < 0)
				break;
		}
		tmp = waitpid(pid, &status, 0);
		if (WIFEXITED(status)) // exit
			pid = WEXITSTATUS(status);
		if (WIFSIGNALED(status)) // signal
			pid = WTERMSIG(status)
 		//mish_exec_signal(p->mish, status);
fprintf(stderr, "waitpid=%i exitstatus=%i\n", tmp, pid); //TEST
		mish_exit_status_set(p->mish, tmp);
(p->mish)->sa.sa_sigaction = handle_signal; /////TEST
		if (mish_exit_status_get(p->mish) == 130)
			return (mish_error_add(p->mish, err_hd_ctrlc, 0, "heredoc ctrl c"));
		if (mish_exit_status_get(p->mish) == 2)
			return (t_process_iofiles_error(p, EACCES, tfile->path));
		close(tfile->fd);
		tfile->fd = open(tfile->path, O_RDONLY | O_CREAT | O_APPEND, 0644);
	}
	return (0);
}
*/













/*
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
			break ;
		}
		if (!ft_strcmp(line, tfile->path))
		{
			free(line);
			break ;
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

int	t_file_heredoc(t_file *tfile, int openfile, t_process *p)
{
	t_file_line_heredoc(tfile, p->mish);
	if (openfile == 0)
	{
		tfile->fd = -1;
		return (0);
	}
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
*/