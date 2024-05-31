/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_03_t_env_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:07:17 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 15:39:19 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_env	*t_env_getvar(t_env *tenv, char *var)
{
	t_env	*env;

	env = tenv;
	if (env == NULL || var == NULL)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(var, env->var) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*t_env_getdata(t_env *env, char *var)
{
	t_env	*varenv;

	if (env == NULL || var == NULL)
		return (NULL);
	varenv = t_env_getvar(env, var);
	if (varenv)
		return (varenv->data);
	return (NULL);
}

int	t_env_setdata(t_env *env, char *var, char *data)
{
	t_env	*varenv;

	if (var == NULL)
		return (-1);
	varenv = t_env_getvar(env, var);
	if (varenv)
	{
		ft_strfree(&(varenv->data));
		if (data)
			varenv->data = strdup(data);
		else
			varenv->data = NULL;
	}
	else
		t_env_add(&env, var, data);
	return (0);
}

void	t_env_print(t_env *tenv)
{
	char	*str;

	while (tenv)
	{
		if (tenv->var && tenv->data)
		{
			str = ft_strjoinva(tenv->var, "=", tenv->data, "\n", NULL);
			write(1, str, ft_strlen(str));
			free(str);
		}
		tenv = tenv->next;
	}
}

int	bashvar_name_isvalid(const char *varname, t_process *process)
{
	int	ret;
	int	i;

	i = 0;
	ret = 1;
	if (varname == NULL || varname[i] == '\0')
		ret = 0;
	if (!ft_isalpha(varname[0]) && varname[0] != '_')
		ret = 0;
	i++;
	while (ret && varname[i])
	{
		if (!ft_isalnum(varname[i]) && varname[i] != '_')
			ret = 0;
		i++;
	}
	if (ret)
		return (1);
	if (process == NULL || process->exitstatus)
		return (0);
	process->exitstatus = 1;
	write(2, "minishell: ", 12);
	write(2, varname, ft_strlen(varname));
	write(2, ": not a valid identifier\n", 26);
	return (0);
}
