/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_09_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/04/26 22:00:34 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

char	*mish_unset_get(t_mish *mish, char *var)
{
	char *str;

	str = t_env_getdata(mish->unset, var);
	return (str);
}

int	mish_unset_set(t_mish *mish, char *var, char *value)
{
	int ret;

	// ajouter verification nom var is ok si var n existe pas deja
	ret = t_env_setstr(mish->unset, var, value);
	return (ret);
}
