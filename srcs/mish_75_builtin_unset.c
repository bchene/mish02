/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_75_builtin_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/23 17:48:22 by bchene           ###   ########.fr       */
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
	char	*str;
	int		i;

	if ((p->ac > 1) && p->av[1][0] == '-')
	{
		str = ft_strjoinva("minishell: unset: ", p->av[1], ": invalid option\n", NULL);
		builtin_error(p, str, 2);
		if (str)
			free (str);
		return ;
	}
	i = 0;
	while(++i < p->ac)
		mish_env_remove(p->mish, p->av[i]);
	mish_exit_status_set(p->mish ,0);
}
