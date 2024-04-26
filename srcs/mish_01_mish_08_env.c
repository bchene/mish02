/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_08_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/04/26 19:34:43 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

char	*mish_env_get(t_mish *mish, char *var)
{
	char *str;

	str = t_env_getdata(mish->env, var);
	return (str);
}

int	mish_env_set(t_mish *mish, char *var, char *value)
{
	int ret;

	if (t_env_getvar(mish->env, var))
		ret = t_env_setstr(mish->env, var, value);
	else
		ret = -1;
	return (ret);
}

int	mish_env_add(t_mish *mish, char *var, char *value)
{
	int ret;
	
	ret = t_env_setstr(mish->env, var, value);
	return (ret);
}
