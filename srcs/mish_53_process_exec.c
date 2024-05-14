/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_53_process_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:12 by bchene            #+#    #+#             */
/*   Updated: 2024/05/14 16:41:31 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_err_type	mish_fork_parent(t_mish *mish)
{
	int	i;
	int	status;
	
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
	mish_p_iofiles_close(mish);
	mish_fds_close(mish);
	i = -1;
	while (++i < mish->nb)
		waitpid((mish->pid)[i], &status, 0);
	mish_exit_status_set(mish, (int)(((status) & 0xff00) >> 8));
	return (t_error_exist(mish->error));
}
/*
	int status;
	waitpid((mish->pid)[i], &status, 0);
	exitstatus = WEXITSTATUS(status);

// mish_exit_status_set(WEXITSTATUS(status));
// ou
// mish_exit_status_set(((status) & 0xff00) >> 8);

old
	i = -1;
	while (++i < mish->nb)
		waitpid((mish->pid)[i], NULL, 0);

*/

t_err_type	t_process_fork_child(t_process *process)
{
	char	**envp;

	if (t_process_dup_io(process))
		return (t_error_exist(process->mish->error));
	if (process->cmd == NULL)
	{
		t_process_builtin(process);
		mish_free(process->mish);
		exit (0);
		//return (mish_error_add(process->mish, err_exit, 0, "exit"));
	}
	else if (access(process->cmd, X_OK) != 0)
		return (mish_error_add(process->mish, err_access, errno, process->cmd));
	envp = mish_env_to_envp(process->mish);
	if (envp == NULL)
		return (mish_error_add(process->mish, err_malloc, errno, \
		"malloc envp"));
	execve(process->cmd, process->av, envp);
	mish_error_add(process->mish, err_execve, errno, "execve");
	if (envp)
		free (envp);
	return (err_execve);
}
