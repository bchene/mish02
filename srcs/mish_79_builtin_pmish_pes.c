/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_79_builtin_pmish_pes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/22 16:15:57 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

/* debug cmd : Command qui affiche mish_print */
void	builtin_pmish(t_process *process)
{
	mish_print(process->mish);
	mish_exit_status_set(process->mish ,0);
}

/* debug cmd : Command qui affiche exit_stat */
void	builtin_pes(t_process *process)
{
	printf("exit status = %i\n", mish_exit_status_get(process->mish));
	mish_exit_status_set(process->mish ,0);
}
