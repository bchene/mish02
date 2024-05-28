/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_76_builtin_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/28 15:53:57 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

/* env with no options or arguments */
void	builtin_env(t_process *process)
{
	if (t_process_is_invalid_option(process))
	{
		if (process->exitstatus == 2)
			process->exitstatus = 125;
		return;
	}
	else if(process->ac > 1)
	{
		if (process->exitstatus == 0)
			builtin_error(process, "minishell: env: too many arguments\n", 127);
		return;
	}
	t_env_print(process->mish->env);
	//process->exitstatus = 0;
}
