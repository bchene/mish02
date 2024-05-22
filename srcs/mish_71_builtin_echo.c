/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_71_builtin_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/22 17:21:17 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"
#include "limits.h"

/* echo with option -n*/
void	builtin_echo(t_process *process)
{
	(void) process;
	mish_exit_status_set(process->mish ,0);
}
