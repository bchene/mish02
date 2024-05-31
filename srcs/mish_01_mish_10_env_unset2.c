/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_10_env_unset2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 13:21:31 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

char	*envstr_var_get(char *str)
{
	int		i;
	char	*var;

	if (str == NULL)
		return (NULL);
	var = NULL;
	i = ft_ischarinstr(str, '=');
	if (i)
	{
		if (i > 1 && str[0] != '+')
			var = ft_strndup(str, i - 1);
		else
			var = ft_strndup(str, i);
	}
	else
		var = strdup(str);
	return (var);
}

char	*envstr_data_get(char *str)
{
	int		i;
	char	*data;

	if (str == NULL)
		return (NULL);
	data = NULL;
	i = ft_ischarinstr(str, '=');
	if (i)
		data = ft_strdup(str + i);
	else
		return (NULL);
	return (data);
}

char	*mish_env_unset_get(t_mish *mish, char *var)
{
	char	*ret;

	ret = mish_env_get(mish, var);
	if (ret)
		return (ret);
	ret = mish_unset_get(mish, var);
	if (ret)
		return (ret);
	return (NULL);
}

int	t_process_env_unset_unset(t_process *process, char *var)
{
	if (mish_unset_get(process->mish, var))
	{
		t_process_unset_remove(process, var);
		return (2);
	}
	if (mish_env_get(process->mish, var))
	{
		t_process_env_remove(process, var);
		return (1);
	}
	return (0);
}
