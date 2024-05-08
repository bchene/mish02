/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_substitute_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:51:15 by locharve          #+#    #+#             */
/*   Updated: 2024/05/07 12:58:48 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

// toujours substituer les variables sauf en cas de simples quotes
// cas particulier ?: $_

int	is_there_a_var(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '$')
		i++;
	if (str && str[i] && (ft_isalpha(str[i + 1])
			|| str[i + 1] == '_'
			|| str[i + 1] == '0'
			|| str[i + 1] == '?'))
		return (i);
	else
		return (-1);
}

char	*get_var_value(t_mish *mish, char *var)
{
	char	*sub;

	//sub = getenv(&var[1]); ////////// mish_get_env
	sub = mish_env_get(mish, &var[1]);
	if (!sub)
		sub = mish_unset_get(mish, &var[1]);
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

char	*substitute_hub(t_mish *mish, char *src, char *var)
{
	char	*dst;

	if (var[1] == '0')
		dst = substitute_0(mish, src, var);
	else if (var[1] == '?')
		dst = substitute_exit_status(mish, src, var);
	else
		dst = substitute_var(mish, src, var);
	return (dst);
}

void	mish_var_dup(t_mish *mish, char **line, char *var)
{
	if (var[1] == '0' || var[1] == '?')
		var = ft_strndup(var, 2);
	else
		var = ft_strndup(var, ft_strlen_while(&var[1],
				is_alphanum_underscore) + 1);
	if (!var)
	{
		mish_error_add(mish, err_malloc, errno, "var_dup");
		return ;
	}
	*line = substitute_hub(mish, *line, var);
	free(var);
	return ;
}

void	mish_substitute_vars(t_mish *mish, char **p_lines)
{
	int		i;
	int		v;

	i = -1;
	while (p_lines && p_lines[++i])
	{
		v = is_there_a_var(p_lines[i]);
		while (v > -1 && is_between_quotes(mish, p_lines[i], v) != 1)
		{
/*			if (p_lines[i][v + 1] == '0' || p_lines[i][v + 1] == '?')
				var = ft_strndup(&p_lines[i][v], 2);
			else
				var = ft_strndup(&p_lines[i][v],
						ft_strlen_while(&p_lines[i][v + 1],
						is_alphanum_underscore) + 1);	//malloc
			if (!var)
				return ;
			p_lines[i] = substitute_hub(mish, p_lines[i], var);
			free(var);
*/			mish_var_dup(mish, &p_lines[i], &p_lines[i][v]);
			printf("substituted ? %s\n", p_lines[i]); /////
			v = is_there_a_var(p_lines[i]);
		}
	}
	return ;
}

void	mish_remove_quotes(t_mish *mish, char **p_lines)
{
	char	*tmp;
	int	i;

	i = 0;
	while (p_lines && p_lines[i])
	{
		if (p_lines[i][0] == '\'' || p_lines[i][0] == '\"')
		{
			tmp = ft_strndup(&p_lines[i][1], ft_strlen(p_lines[i]) - 2);
			if (!tmp)
			{
				mish_error_add(mish, err_malloc,
						errno, "mish_remove_quotes");
				return ;
			}
			free(p_lines[i]);
			p_lines[i] = tmp;
		}
		i++;
	}
}
