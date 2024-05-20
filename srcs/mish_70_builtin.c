/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_70_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/20 19:00:50 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	t_process_builtin(t_process *process)
{
	char *cmd;

	cmd = (process->av)[0];
	if (cmd == NULL) 
		builtin_no_cmd(process);
	if (!ft_strcmp(cmd, "echoTEST")) 
		builtin_echo(process);
	else if (!ft_strcmp(cmd, "cd"))
		builtin_cd(process);
	else if (!ft_strcmp(cmd, "pwd"))
		builtin_pwd(process);
	else if (!ft_strcmp(cmd, "exportTEST"))
		builtin_export(process);
	else if (!ft_strcmp(cmd, "unsetTEST"))
		builtin_unset(process);
	else if (!ft_strcmp(cmd, "env"))
		builtin_env(process);
	else if (!ft_strcmp(cmd, "no_access_cmd"))
		builtin_no_access_cmd(process);
	else if (!ft_strcmp(cmd, "pmish"))
		builtin_pmish(process);
}

void	builtin_free(t_process *process)
{
	int exstat;

	mish_error_treat(process->mish);
	t_error_lst_free(&(process->mish->error));
	exstat = mish_exit_status_get(process->mish);
	mish_free(process->mish, 0);
	exit (exstat);
}

void	builtin_error(t_process *p,char *str, int exitstatus)
{
	write(2, str, ft_strlen(str));
	if (p->index == p->mish->nb - 1)
		mish_exit_status_set(p->mish, exitstatus);
}
