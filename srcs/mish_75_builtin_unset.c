/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_75_builtin_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/30 13:47:04 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"
/*
	si va[1][0] == '-'
		bash: unset: -a: invalid option
	
	unset "invalid-variable-name"  # Cela provoquera une erreur

*/

/* export with no options */
void	builtin_unset(t_process *p)
{
	int		i;

	if (p->exitstatus == 0)
		p->exitstatus = -1;
	i = 0;
	while(++i < p->ac)
		t_process_env_remove(p, p->av[i]);
	if (p->exitstatus == -1)
		p->exitstatus = 0;
}
