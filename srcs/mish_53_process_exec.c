/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_53_process_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:12 by bchene            #+#    #+#             */
/*   Updated: 2024/05/29 16:59:23 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_err_type	mish_exec(t_mish *mish)
{
	int	i;
	int	status;

	status = 0;
	if (mish->nb == 1 && (mish->p + 0)->cmd == NULL)
		t_process_exec_builtin(mish->p + 0);
	else
	{
		if(mish_fork_parent(mish) == err_none)
		{
			mish_p_iofiles_close(mish);
			mish_fds_close(mish);
			i = mish->nb - 1;
			waitpid((mish->pid)[i], &status, 0);
			if((mish->p + i)->exitstatus == 0)
				mish_exit_status_set(mish, (int)(((status) & 0xff00) >> 8));
			if (WTERMSIG(status) == SIGINT)
			{
				// CTRLC
				// if (g_signal == SIGINT)
				//		mettre exit stat a 128 + SIGINT = 130
				// 		mettre g_dignal = 0
				//		PAS DE MESSAGE
				(mish->p + i)->exitstatus = 130; // WTERMSIG(status) + 128
				g_signal = 0;
			}
			if (WTERMSIG(status) == SIGQUIT)
			{
				// CTRL BACKSLASH
				// if (g_signal == SIGQUIT)	
				// 		mettre exit stat a 128 + SIGQUIT = 131
				// 		mettre g_dignal = 0
				//		si derniere process non termine
				//			"^\Quit (core dumped)\n"
				// 		sinon
				//			affchie "^" a priori rien a jouter.
				(mish->p + i)->exitstatus = 131; // WTERMSIG(status) + 128
				g_signal = 0;
				write(2, "^\\Quit (core dumped)\n", 22);
			}
			else
				mish_exit_status_set(mish, (mish->p + i)->exitstatus);
			while (--i >= 0)
				waitpid((mish->pid)[i], &status, 0);
		}
	}
	return (t_error_exist(mish->error));
}

t_err_type	t_process_exec_builtin(t_process *p)
{
	mish_fds_close(p->mish);
	if (t_process_dup_io_builtin(p))
		return (t_error_exist(p->mish->error));
	t_process_builtin(p);
	if (p->fdinbkp > 2)
	{
		if (dup2(p->fdinbkp, STDIN_FILENO) == -1)
			return (mish_error_add(p->mish, err_dup2, errno, "dup fdinbkp"));
		close_reset_fd(&(p->fdinbkp));
	}
	if (p->fdoutbkp > 2)
	{
		if (dup2(p->fdoutbkp, STDOUT_FILENO) == -1)
			return (mish_error_add(p->mish, err_dup2, errno, "dup fdoutbkp"));	
		close_reset_fd(&(p->fdoutbkp));
	}
	mish_exit_status_set(p->mish, p->exitstatus);
	return (t_error_exist(p->mish->error));
}

t_err_type	mish_fork_parent(t_mish *mish)
{
	int	i;
	
	i = 0;
	while (i < mish->nb) //&& mish_continue(mish)
	{
		if (t_process_pipe_fds((mish->p) + i))
			return (t_error_exist(mish->error));
		mish->pid[i] = fork();
		if (mish->pid[i] == -1)
			return (mish_error_add(mish, err_fork, errno, "fork() == -1"));
		if (mish->pid[i] == 0)
		{
			t_process_fork_child((mish->p) + i);
			return (mish_continue(mish));
		}
		i++;
	}
	return (t_error_exist(mish->error));
}

t_err_type	t_process_fork_child(t_process *process)
{
	char	**envp;
	int		exitstatus;

	if (t_process_dup_io(process))
		return (t_error_exist(process->mish->error));
	if (process->cmd == NULL)
		t_process_builtin(process);
	envp = mish_env_to_envp(process->mish);
	if (envp == NULL)
		return (mish_error_add(process->mish, err_malloc, errno, \
		"malloc envp"));
	execve(process->cmd, process->av, envp);
	if (process->exitstatus == 0)
	{
		if (errno == EACCES)
			builtin_perror(process, errno, NULL, 126);
		else
			builtin_perror(process, errno, NULL, 127);
	}
	ft_freesplit (envp);
	exitstatus = process->exitstatus;
	mish_free(process->mish, 0);
	exit(exitstatus);
}
