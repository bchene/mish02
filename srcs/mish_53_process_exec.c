/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_53_process_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:12 by bchene            #+#    #+#             */
/*   Updated: 2024/05/06 15:09:42 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_err_type	mish_create_process(t_mish *mish)
{
	int	i;

	mish_p_malloc(mish);
	if (mish->error->err_no)
		mish_fds_malloc(mish);
	if (mish->error->err_no)
	{
		i = -1;
		while(++i < mish->nb && mish->error->err_no)
		{
			//t_process_set(mish, i, (mish->line)[i]);
			//t_process_get_iofiles((mish->p)[i]);
			//t_process_get_cmd((mish->p)[i]);
		}
	}
	return (mish->error->err_no);
}

void	t_process_fork_child(t_process *process)
{
	char	**envp;

	t_process_dup_io(process);
	// A FAIRE : Detection cmd = fonction interne
	if (access(process->cmd, X_OK) == 0)
	{
		envp = mish_env_to_envp(process->mish);
		if (envp == NULL)
			mish_error_add(process->mish, err_malloc, errno, "malloc envp");
		else if (execve(process->cmd, process->av, envp) == -1)
			mish_error_add(process->mish, err_fork, errno, "execve");
		if (envp)
			free (envp);
	}
	else
	{
		mish_error_add(process->mish, err_fork, errno, "access");
		write(2, "EXECVE PROBLEME\n", 17); // TEST
	}
	// sortie erreur
	mish_free(process->mish);		// FIN ERR
	exit (EXIT_FAILURE);		// FIN ERR
}

t_err_type	mish_fork_parent(t_mish *mish)
{
	int			i;
	t_process	*process;

	i = 0;
	while (i < mish->nb) //&& mish_continue(mish)
	{
		//printf("%i\n", i);
		process = (mish->p) + i;
		t_process_pipe_fds(process);
		mish->pid[i] = fork();
		if (mish->pid[i] == -1)
			mish_error_add(mish, err_fork, errno, "fork() == -1");
		if (mish->pid[i] == 0)
			t_process_fork_child(process);
		i++;
	}
	mish_fds_close(mish);
	i = -1;
	while (++i < mish->nb)
		waitpid((mish->pid)[i], NULL, 0);
	return (t_error_exist(mish->error));
}
