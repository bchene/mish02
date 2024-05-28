/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_09_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/28 14:00:45 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

char	*mish_unset_get(t_mish *mish, char *var)
{
	char	*str;

	if (bashvar_name_isvalid(var, NULL))
	{
		str = t_env_getdata(mish->unset, var);
		return (str);
	}
	return (NULL);
}

int	t_process_unset_set(t_process *process, char *var, char *value)
{
	int	ret;

	if (bashvar_name_isvalid(var, process))
	{
		if (t_env_getvar(process->mish->unset, var))
			ret = t_env_setdata(process->mish->unset, var, value);
		else
			ret = 0;
		return (ret);
	}
	return (0);	
}

int	t_process_unset_remove(t_process *process, char *var)
{
	t_env	*tenv;

	if (bashvar_name_isvalid(var, process) == 0)
		return (0);
	tenv = t_env_getvar(process->mish->unset, var);
	if (tenv)
	{
		t_env_remove(&(process->mish->unset), tenv);
		return (1);
	}
	return (0);
}

int	t_process_unset_export(t_process *process, char *var, char *value)
{
	if (mish_unset_get(process->mish, var))
	{
		t_process_unset_remove(process, var);
	}
	if (mish_env_get(process->mish, var))
	{
		t_process_env_set(process, var, value);
		return (2);
	}
	else
	{
		if (t_process_env_add(process, var, value))
			return (1);
	}
	return (0);
}
