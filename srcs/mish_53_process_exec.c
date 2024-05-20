/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_53_process_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:12 by bchene            #+#    #+#             */
/*   Updated: 2024/05/20 20:13:46 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	mish_cd(t_process *p)
{
	char		*pwd;

	if (p->ac == 1)
		return ;
	if (p->ac == 2)
	{
		if (p->av[1][0] != '/')
		{
			p->av[1] = ft_strjointoleft(p->av[1], "/");
			p->av[1] = \
			ft_strjointoleft(p->av[1], mish_env_get(p->mish, "PWD"));
		}
		if (chdir(p->av[1]))
			perror(p->av[1]);
		else
		{
			pwd = malloc(1024 * sizeof(char));
			getcwd(pwd, 1024);
			mish_env_set(p->mish, "OLDPWD", mish_env_get(p->mish, "PWD"));
			mish_env_set(p->mish, "PWD", pwd);
			free(pwd);
		}	
	}
	else
		builtin_error(p, "minishell: cd: too many arguments\n", 2);
}

t_err_type	mish_exec(t_mish *mish)
{
	int	i;
	int	status;

	if (mish->nb == 1 && !ft_strcmp(mish->p->av[0], "cd"))
		mish_cd(mish->p + 0);
	else
	{
		if(mish_fork_parent(mish) == err_none)
		{
			mish_p_iofiles_close(mish);
			mish_fds_close(mish);
			i = mish->nb;
			while (--i >= 0)
				waitpid((mish->pid)[i], &status, 0);
			mish_exit_status_set(mish, (int)(((status) & 0xff00) >> 8));
		}
	}
	return (t_error_exist(mish->error));
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

	if (t_process_dup_io(process))
		return (t_error_exist(process->mish->error));
	if (process->cmd == NULL)
	{
		t_process_builtin(process);
		mish_free(process->mish, 0);	//?
		exit (0);					//?
		//return (mish_error_add(process->mish, err_exit, 0, "exit"));
	}
	else if (access(process->cmd, X_OK) != 0)
		builtin_no_access_cmd(process);
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
