/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_74_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 16:08:58 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
bash: export: `bloup2'1ceci= est un texte1'2': not a valid identifier
exsta =1

*/

#include "mish.h"

static int	t_env_size(t_env *tenv)
{
	int	i;

	i = 0;
	while (tenv)
	{
		i ++;
		tenv = tenv->next;
	}
	return (i);
}

static char	**t_env_splitenv_get(t_env *env)
{
	char	**splitenv;
	int		i;

	i = t_env_size(env);
	splitenv = malloc((i + 1) * sizeof(char *));
	splitenv[i] = NULL;
	while (env)
	{
		i--;
		if (env->data)
			splitenv[i] = \
			ft_strjoinva(env->var, "=\"", env->data, "\"\n", NULL);
		else
			splitenv[i] = ft_strjoinva(env->var, "\n", NULL);
		env = env->next;
	}
	return (splitenv);
}

static void	builtin_export_print(t_process *process)
{
	char	**splitenv;
	int		i;

	splitenv = t_env_splitenv_get(process->mish->env);
	ft_sort_split(splitenv);
	i = 0;
	while (splitenv[i])
	{
		printf("declare -x %s", splitenv[i]);
		i++;
	}
	ft_freesplit(splitenv);
}

static void	env_export_str(t_process *p, char *str)
{
	int		i;
	char	*var;
	char	*data;

	i = ft_ischarinstr(str, '=');
	if (i)
	{
		if (i > 2 && str[i - 2] == '+')
		{
			var = ft_strndup(str, i - 2);
			data = ft_strdup(mish_env_get(p->mish, var));
			data = ft_strjointo(data, str + i);
		}
		else
		{
			var = ft_strndup(str, i - 1);
			data = ft_strdup(str + i);
		}
		t_process_env_add(p, var, data);
		ft_strfree(&var);
		ft_strfree(&data);
	}
	else if (mish_env_get(p->mish, str) == NULL)
		t_process_env_add(p, str, NULL);
}

/* export with no options */
void	builtin_export(t_process *process)
{
	int	i;

	if (process->ac == 1)
		builtin_export_print(process);
	else if (t_process_is_invalid_option(process))
		return ;
	else
	{
		i = 0;
		while (++i < process->ac)
			if (process->av[i])
				env_export_str(process, process->av[i]);
	}
}
