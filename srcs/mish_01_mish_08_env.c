/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_08_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/08 18:23:59 by bchene           ###   ########.fr       */
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
	
	// ajouter verification nom var is ok si var n existe pas deja
	ret = t_env_setstr(mish->env, var, value);
	return (ret);
}

int	mish_env_remove(t_mish *mish, char *var)
{
	t_env	*tenv;

	tenv = t_env_getvar(mish->env, var);
	if (tenv)
	{
		t_env_remove(&(mish->env), tenv);
		return (1);
	}
	return (0);
}

char	**mish_env_to_envp(t_mish *mish)
{
	int		nb;
	int		i;
	t_env	*tmp;
	char	**ret;

	nb = 0;
	tmp = mish->env;
	while (tmp)
	{
		nb++;
		tmp = tmp->next;
	}
	ret = ft_calloc(nb + 1, sizeof(char *));
	i = -1;
	tmp = mish->env;
	while (++i < nb)
	{
		ret[i] = tmp->str;
		tmp = tmp->next;
	}
	return (ret);
}

/*
int	mish_env_change_value(t_mish *mish, t_env *env_or_u, char *var, char *value)
{
	t_env	*to_change;
	char	*str;
	size_t	len_var;

	to_change = t_env_getvar(env_or_u, var);
	if (to_change)
	{
		len_var = ft_strlen(var);
		str = ft_calloc(len_var + 1 + ft_strlen(value) + 1, sizeof(char));
		if (str)
		{
			ft_strcpy(str, var);
			str[len_var] = '=';
			ft_strcpy(&str[len_var + 1], value);
			free(to_change->str);
			to_change->str = str;
		}
		else
			return (mish_error_add(mish, err_malloc,
					errno, "mish_env_change_value"));
	}
	return (0);
}
*/