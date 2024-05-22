/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_70_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/22 19:57:14 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	t_process_builtin(t_process *process)
{
	if ((process->av)[0] == NULL) 
		builtin_no_cmd(process);
	if (!ft_strcmp((process->av)[0], "echo")) 
		builtin_echo(process);
	else if (!ft_strcmp((process->av)[0], "cd"))
		builtin_cd(process);
	else if (!ft_strcmp((process->av)[0], "pwd"))
		builtin_pwd(process);
	else if (!ft_strcmp((process->av)[0], "export"))
		builtin_export(process);
	else if (!ft_strcmp((process->av)[0], "unset"))
		builtin_unset(process);
	else if (!ft_strcmp((process->av)[0], "env"))
		builtin_env(process);
	else if (!ft_strcmp((process->av)[0], "exit"))
		builtin_exit(process);
	else if (!ft_strcmp((process->av)[0], "pmish"))
		builtin_pmish(process);
	else if (!ft_strcmp((process->av)[0], "pes"))
		builtin_pes(process);
	else
		builtin_no_access_cmd(process);
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

