/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_70_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/14 15:21:41 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	mish_builtin_echo(t_process *process)
{
	(void) process;
}

void	mish_builtin_cd(t_process *process)
{
	(void) process;
}

void	mish_builtin_pwd(t_process *process)
{
	(void) process;
}

void	mish_builtin_export(t_process *process)
{
	(void) process;
}

void	mish_builtin_unset(t_process *process)
{
	(void) process;
}

void	mish_builtin_env(t_process *process)
{
	(void) process;
}

void	mish_builtin_empty_cmd(t_process *process)
{
	(void) process;
}

void	t_process_builtin(t_process *process)
{
	if (!ft_strncmp((process->av)[0], "echoTEST", ft_strlen("echoTEST")))
		mish_builtin_echo(process);
	else if (!ft_strncmp((process->av)[0], "cdTEST", ft_strlen("cdTEST")))
		mish_builtin_cd(process);
	else if (!ft_strncmp((process->av)[0], "pwdTEST", ft_strlen("pwdTEST")))
		mish_builtin_pwd(process);
	else if (!ft_strncmp((process->av)[0], "exportTEST", ft_strlen("exportTEST")))
		mish_builtin_export(process);
	else if (!ft_strncmp((process->av)[0], "unsetTEST", ft_strlen("unsetTEST")))
		mish_builtin_unset(process);
	else if (!ft_strncmp((process->av)[0], "envTEST", ft_strlen("envTEST")))
		mish_builtin_env(process);
	else if (!ft_strncmp((process->av)[0], "empty_cmd", ft_strlen("empty_cmd")))
		mish_builtin_empty_cmd(process);
}
