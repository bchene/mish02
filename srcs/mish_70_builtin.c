/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_70_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/16 13:42:21 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	builtin_echo(t_process *process)
{
	(void) process;
}

void	builtin_cd(t_process *process)
{
	(void) process;
}

void	builtin_pwd(t_process *process)
{
	(void) process;
}

void	builtin_export(t_process *process)
{
	(void) process;
}

void	builtin_unset(t_process *process)
{
	(void) process;
}

void	builtin_env(t_process *process)
{
	t_env_print(process->mish->env);
	builtin_free(process);
}

void	builtin_empty_cmd(t_process *process)
{
	builtin_free(process);
}

void	builtin_pmish(t_process *process)
{
	mish_print(process->mish);
	builtin_free(process);
}

void	builtin_free(t_process *process)
{
	int exstat;

	mish_error_treat(process->mish);
	t_error_lst_free(&(process->mish->error));
	exstat = mish_exit_status_get(process->mish);
	mish_free(process->mish);
	exit (exstat);
}

void	builtin_no_access(t_process *process)
{
	mish_error_add(process->mish, err_access, 13, process->cmd);
	builtin_free(process);
}

void	t_process_builtin(t_process *process)
{
	char *cmd;

	cmd = (process->av)[0];
	if (!ft_strncmp(cmd, "echoTEST", ft_strlen(cmd) + 1))
		builtin_echo(process);
	else if (!ft_strncmp(cmd, "cdTEST", ft_strlen(cmd) + 1))
		builtin_cd(process);
	else if (!ft_strncmp(cmd, "pwdTEST", ft_strlen(cmd) + 1))
		builtin_pwd(process);
	else if (!ft_strncmp(cmd, "exportTEST", ft_strlen(cmd) + 1))
		builtin_export(process);
	else if (!ft_strncmp(cmd, "unsetTEST", ft_strlen(cmd) + 1))
		builtin_unset(process);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd) + 1))
		builtin_env(process);
	else if (!ft_strncmp(cmd, "empty_cmd", ft_strlen(cmd) + 1))
		builtin_empty_cmd(process);
	else if (!ft_strncmp(cmd, "pmish", ft_strlen(cmd) + 1))
		builtin_pmish(process);
}
