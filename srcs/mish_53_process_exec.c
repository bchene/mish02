/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_53_process_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:12 by bchene            #+#    #+#             */
/*   Updated: 2024/05/10 14:43:46 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

// INUTILE OU A REVOIR POUR LANCEMENT EXECUTION
t_err_type	mish_start_process(t_mish *mish)
{
	int	i;

	if (mish_path_set(mish))
		return (t_error_exist(mish->error));
	mish->nb = ft_splitsize(mish->splitline);
	if (mish_p_malloc(mish))
		return (t_error_exist(mish->error));
	if (mish_fds_malloc(mish))
		return (t_error_exist(mish->error));
	if (mish_pid_malloc(mish))
		return (t_error_exist(mish->error));
	i = -1;
	while (++i < mish->nb)
	{
		if (mish_p_init(mish, i, NULL))
			return (t_error_exist(mish->error));
		// on rempli iofiles
		// on rempli ac et av
		// on ouvre les iofiles
		main_test_open_files((mish->p) + i); //TEST
		t_process_cmd_get((mish->p) + i); // A METRE dans init p apres traitement de ligne
	}
	if (mish_fork_parent(mish))
		return (t_error_exist(mish->error));
	return (0);
}

t_err_type	mish_fork_parent(t_mish *mish)
{
	int			i;

	i = 0;
	while (i < mish->nb) //&& mish_continue(mish)
	{
		if (t_process_pipe_fds((mish->p) + i))
			return (t_error_exist(mish->error));
		mish->pid[i] = fork();
		if (mish->pid[i] == -1)
			return(mish_error_add(mish, err_fork, errno, "fork() == -1"));
		if (mish->pid[i] == 0)
			t_process_fork_child((mish->p) + i);
		i++;
	}
	mish_p_iofiles_close(mish);
	mish_fds_close(mish);
	i = -1;
	while (++i < mish->nb)
		waitpid((mish->pid)[i], NULL, 0);
	return (t_error_exist(mish->error));
}

t_err_type	t_process_fork_child(t_process *process)
{
	char	**envp;

	if (t_process_dup_io(process))
		return (t_error_exist(process->mish->error));
	// A FAIRE : Detection cmd = fonction interne
	if (access(process->cmd, X_OK) == 0)
	{
		envp = mish_env_to_envp(process->mish);
		if (envp == NULL)
			return (mish_error_add(process->mish, err_malloc, errno, "malloc envp"));
		else if (execve(process->cmd, process->av, envp) == -1)
			return (mish_error_add(process->mish, err_fork, errno, "execve"));
		if (envp)
			free (envp);
	}
	else
		return (mish_error_add(process->mish, err_fork, errno, "access"));
	// sortie erreur
	mish_free(process->mish);	// FIN ERR
	exit (EXIT_FAILURE);		// FIN ERR
}

/*
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
*/