/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_08_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/28 13:50:51 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

char	*mish_env_get(t_mish *mish, char *var)
{
	char	*str;

	if (bashvar_name_isvalid(var, NULL))
	{
		str = t_env_getdata(mish->env, var);
		return (str);
	}
	return (NULL);
}

int	t_process_env_set(t_process *process, char *var, char *value)
{
	int	ret;

	if (bashvar_name_isvalid(var, process))
	{
		if (t_env_getvar(process->mish->env, var))
			ret = t_env_setdata(process->mish->env, var, value);
		else
			ret = 0;
		return (ret);
	}
	return (0);
}

int	t_process_env_add(t_process *process, char *var, char *value)
{
	int	ret;

	if (bashvar_name_isvalid(var, process) == 0)
		return (0);
	else
		ret = t_env_setdata(process->mish->env, var, value);
	return (ret);
}

int	t_process_env_remove(t_process *process, char *var)
{
	int		ret;
	t_env	*tenv;

	if (bashvar_name_isvalid(var, process) == 0)
		return (0);
	tenv = t_env_getvar(process->mish->env, var);
	if (tenv)
	{
		ret = t_env_remove(&(process->mish->env), tenv);
		return (ret);
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
	while (++i < nb && tmp)
	{
		if (tmp->var && tmp->data)
			ret[i] = ft_strjoinva(tmp->var, "=", tmp->data, NULL);
		tmp = tmp->next;
	}
	return (ret);
}
