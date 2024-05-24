/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_74_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/24 12:42:39 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
bash: export: `bloup2'1ceci= est un texte1'2': not a valid identifier
exsta =1

*/

#include "mish.h"

static void	builtin_export_print(t_process *process)
{
	(void) process;
}

static void	env_export_str(t_mish *mish, char *str)
{
	int i;
	char *var;
	char *data;

	var = NULL;
	data = NULL;
	i = ft_ischarinstr(str, '=');
	if (i)
	{
		if (i > 2 && str[i - 2] == '+')
		{
			var = ft_strndup(str, i - 2);
			data = ft_strjointo(mish_env_get(mish, var) ,str + i);
		}
		else if(i > 1 && str[0] != '+')
		{
			var = ft_strndup(str, i - 1);
			data = ft_strdup(str + i);
		}
		mish_env_add(mish, var, data);
		ft_strfree(&var);
		ft_strfree(&data);
	}
	else
		mish_env_add(mish, str, NULL);
}

/* export with no options */
void	builtin_export(t_process *process)
{
	int	i;

	if (process->ac == 1)
		builtin_export_print(process);
	else if (t_process_is_invalid_option(process))
		return;
	else
	{
		i = 0;
		while(++i < process->ac)
			if (process->av[i])
				env_export_str(process->mish, process->av[i]);
	}
	mish_exit_status_set(process->mish ,0);
}
