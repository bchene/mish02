/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_10_env_unset.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 15:04:45 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

static void	mish_env_init(t_mish *mish, char **envp)
{
	int		i;
	char	*var;
	char	*data;

	i = 0;
	while (envp && envp[i])
	{
		var = envstr_var_get(envp[i]);
		data = envstr_data_get(envp[i]);
		t_env_add(&(mish->env), var, data);
		ft_strfree(&var);
		ft_strfree(&data);
		i++;
	}
	if (mish_env_get(mish, "SHLVL"))
	{
		data = ft_itoa(ft_atoi(mish_env_get(mish, "SHLVL")) + 1);
		if (data)
		{
			t_env_setdata(mish->env, "SHLVL", data);
			free(data);
		}
		else
			mish_error_add(mish, err_malloc, errno, "SHLVL env init");
	}
}

static void	mish_unset_init(t_mish *mish)
{
	int		i;
	char	**split;

	split = \
	ft_split("$, ,0,minishell,1, ,2, ,3, ,4, ,5, ,6, ,7, ,8, ,9, ,?,0", ',');
	if (split)
	{
		free(split[1]);
		split[1] = ft_itoa(getpid());
		if (split[1] == NULL)
		{
			split[1] = ft_strempty(NULL);
			ft_freesplit(split);
		}
	}
	i = 0;
	while (split && split[i])
	{
		t_env_add(&(mish->unset), split[i], split[i + 1]);
		i += 2;
	}
	if (split == NULL)
		mish_error_add(mish, err_malloc, errno, "SHLVL env init");
	ft_freesplit(split);
}

void	mish_env_unset_init(t_mish *mish, char **envp)
{
	mish_env_init(mish, envp);
	mish_unset_init(mish);
}

void	mish_env_unset_free(t_mish *mish)
{
	t_env_free(&(mish->env));
	t_env_free(&(mish->unset));
}

void	mish_env_unset_print(t_mish *mish)
{
	t_env	*tmp;

	printf("///   env :\n");
	tmp = mish->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->var, tmp->data);
		tmp = tmp->next;
	}
	printf("///   unset :\n");
	tmp = mish->unset;
	while (tmp)
	{
		printf("%s=%s\n", tmp->var, tmp->data);
		tmp = tmp->next;
	}
}
