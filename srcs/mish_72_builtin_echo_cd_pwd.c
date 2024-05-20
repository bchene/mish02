/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_72_builtin_echo_cd_pwd.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/20 20:17:39 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"
#include "limits.h"

void	builtin_echo(t_process *process)
{
	(void) process;
}

void	builtin_cd(t_process *p)
{
	if (p->ac != 1 && p->ac != 2)
		builtin_error(p, "minishell: cd: too many arguments\n", 2);
	builtin_no_cmd(p);
}

void	builtin_pwd(t_process *process)
{
	char *pwd;

	if (process->ac == 1)
	{
		pwd = mish_env_get(process->mish, "PWD");
		if (pwd)
			printf("%s\n", pwd);
	}
	else
		builtin_error(process, "minishell: pwd: too many arguments\n", 2);
}
