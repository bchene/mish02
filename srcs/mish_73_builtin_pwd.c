/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_73_builtin_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/23 15:32:05 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"
#include "limits.h"

/* pwd with no options */
void	builtin_pwd(t_process *process)
{
	char *pwd;

	if ((process->ac > 1) && process->av[1][0] == '-')
	{
		pwd = ft_strjoinva("minishell: pwd: ", process->av[1], ": invalid option\n", NULL);
		builtin_error(process, pwd, 2);
		free (pwd);
		return ;
	}
	pwd = mish_env_get(process->mish, "PWD");
	if (pwd)
	{
		printf("%s\n", pwd);
		mish_exit_status_set(process->mish ,0);
	}
}
