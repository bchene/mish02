/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_75_builtin_nocmd_pmish.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/20 18:06:06 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	builtin_no_cmd(t_process *process)
{
	builtin_free(process);
}

void	builtin_no_access_cmd(t_process *process)
{
	mish_error_add(process->mish, err_access, 13, process->cmd);
	builtin_free(process);
}

void	builtin_pmish(t_process *process)
{
	mish_print(process->mish);
	builtin_free(process);
}
