/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_70_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/22 16:19:39 by bchene           ###   ########.fr       */
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
	else if (!ft_strcmp(cmd, "pes"))
		builtin_pes(process);
	builtin_free(process);
}

void	builtin_free(t_process *process)
{
	int exstat;

	if (process->mish->nb > 1)
	{
		mish_error_treat(process->mish);
		t_error_lst_free(&(process->mish->error));
		exstat = mish_exit_status_get(process->mish);
		mish_free(process->mish, 0);
		fprintf(stderr, "exit(%i)\n", exstat);
		exit (exstat);
	}
}

void	builtin_error(t_process *p,char *str, int exitstatus)
{
	write(2, str, ft_strlen(str));
	mish_exit_status_set(p->mish, exitstatus);
}

void	builtin_perror(t_process *p,int err ,char *str, int exitstatus)
{
	char	*s;

	//s = ft_strjoin_va("minishell :", p->av + 0, " :", str, " :", strerror(err));
	s = ft_strjoin("minishell :", p->av[0]);
	if (s)
	{
		if (str)
		{
			s = ft_strjointo(s, " :");
			s = ft_strjointo(s, str);
		}
		if (strerror(err))
		{
			s = ft_strjointo(s, " :");
			s = ft_strjointo(s, strerror(err));
		}
		s = ft_strjointo(s, "\n");
		write(2, s, ft_strlen(s));
		free(s);
	}
	mish_exit_status_set(p->mish, exitstatus);
}

