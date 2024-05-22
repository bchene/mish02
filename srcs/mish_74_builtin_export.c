/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_74_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/22 16:16:05 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

/* export with no options */
void	builtin_export(t_process *process)
{
	(void) process;
	mish_exit_status_set(process->mish ,0);
}
