/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_78_builtin_nocmd_noaccess.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 16:33:59 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

/* empty cmd with no args */
void	builtin_no_cmd(t_process *process)
{
	(void) process;
}

/* minishell: Command 'p->cmd' not found */
void	builtin_no_access_cmd(t_process *process)
{
	if (process->exitstatus)
		return ;
	if (access((process->av)[0], X_OK))
	{
		process->exitstatus = 127;
		write(2, "Command '", 10);
		write(2, (process->av)[0], ft_strlen((process->av)[0]));
		write(2, "' not found\n", 13);
	}
}
