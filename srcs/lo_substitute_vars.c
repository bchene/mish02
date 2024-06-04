/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_substitute_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:51:15 by locharve          #+#    #+#             */
/*   Updated: 2024/06/04 16:38:03 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

int	is_there_a_var(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && (str[i] != '$' || is_between_quotes(str, i) == 1))
		i++;
	if (is_between_quotes(str, i) && is_in_str("\'\"", str[i + 1]))
		return (-1);
	if (str && str[i] && str[i + 1] \
	&& (str[i + 1] == '?' || str[i + 1] == '$' \
	|| is_alphanum_underscore(str[i + 1]) \
	|| is_in_str("\'\"", str[i + 1])))
		return (i);
	else
		return (-1);
}

char	*get_var_value(t_mish *mish, char *var)
{
	char	*sub;

	sub = mish_env_unset_get(mish, &var[1]);
	if (sub)
	{
		sub = ft_strdup(sub);
		if (!sub)
			mish_error_add(mish, err_malloc, errno, "get_var_value");
	}
	else
		sub = ft_calloc(1, sizeof(char));
	return (sub);
}
