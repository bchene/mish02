/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_09_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/15 15:23:54 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

char	*mish_unset_get(t_mish *mish, char *var)
{
	char	*str;

	str = t_env_getdata(mish->unset, var);
	return (str);
}

int	mish_unset_set(t_mish *mish, char *var, char *value)
{
	int	ret;

	// ajouter verification nom var is ok si var n existe pas deja
	ret = t_env_setstr(mish->unset, var, value);
	return (ret);
}

int	mish_unset_remove(t_mish *mish, char *var)
{
	t_env	*tenv;

	tenv = t_env_getvar(mish->unset, var);
	if (tenv)
	{
		t_env_remove(&(mish->unset), tenv);
		return (1);
	}
	return (0);
}

int	mish_unset_export(t_mish *mish, char *var, char *value)
{
	if (mish_unset_get(mish, var))
	{
		mish_unset_remove(mish, var);
	}
	if (mish_env_get(mish, var))
	{
		mish_env_set(mish, var, value);
		return (2);
	}
	else
	{
		if (mish_env_add(mish, var, value))
			return (1);
	}
	return (0);
}

int	mish_unset_valid_name(char *str)
{
	int	i;

	if (str && !ft_isdigit(str[0]))
	{
		i = 1;
		while (str[i] && is_alphanum_underscore(str[i]))
			i++;
		return (i);
	}
	return (0);
}
