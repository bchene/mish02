/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_10_env_unset.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/15 18:32:19 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	mish_env_unset_init(t_mish *mish, char **envp)
{
	int		i;
	char	*value;

	i = 0;
	while (envp && envp[i])
	{
		t_env_add(&(mish->env), envp[i]);
		i++;
	}
	t_env_add(&(mish->unset), "?=0");
	t_env_add(&(mish->unset), "0=minishell");
	if (mish_env_get(mish, "SHLVL"))
	{
		i = ft_atoi(mish_env_get(mish, "SHLVL")) + 1;
		value = ft_itoa(i);
		if (value)
		{
			mish_env_set(mish, "SHLVL", value);
			free(value);
		}
		else
			mish_error_add(mish, err_malloc, errno, "SHLVL env init");
	}
}

void	mish_env_unset_free(t_mish *mish)
{
	t_env_free(&(mish->env));
	t_env_free(&(mish->unset));
}

char	*mish_env_unset_get(t_mish *mish, char *var)
{
	char *ret;

	ret = mish_env_get(mish, var);
	if(ret)
		return (ret);
	ret = mish_unset_get(mish, var);
	if(ret)
		return (ret);
	return (NULL);
}

int	mish_env_unset_unset(t_mish *mish, char *var)
{
	if (mish_unset_get(mish, var))
	{
		mish_unset_remove(mish, var);
		return (2);
	}
	if (mish_env_get(mish, var))
	{
		mish_env_remove(mish, var);
		return (1);
	}
	return (0);
}

void	mish_env_unset_print(t_mish *mish)
{
	t_env	*tmp;

	printf("///   env :\n");
	tmp = mish->env;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
	printf("///   unset :\n");
	tmp = mish->unset;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}
