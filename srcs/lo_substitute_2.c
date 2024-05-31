/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_substitute_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:15:09 by locharve          #+#    #+#             */
/*   Updated: 2024/05/31 15:24:42 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	mish_var_dup(t_mish *mish, char **line, char *var)
{
	if (ft_isdigit(var[1]) || var[1] == '?' || var[1] == '$')
		var = ft_strndup(var, 2);
	else if (is_in_str("\'\"", var[1]))
		var = ft_strndup(var, 1);
	else
		var = ft_strndup(var, ft_strlen_while(&var[1],
				is_alphanum_underscore) + 1);
	if (!var)
	{
		mish_error_add(mish, err_malloc, errno, "var_dup");
		return ;
	}
	*line = substitute_var(mish, *line, var);
	free(var);
	return ;
}

char    *mish_substitute_str(t_mish *mish, int f(char *, int), char *str)
{
    int v;

    if (str)
    {
        v = is_there_a_var(str);
        while (v >= 0 && (!f || f(str, v) != 1))
        {
			// printf("var = %s\n", &str[v]); /////
            if (!f || f(str, v) != 1)
			{
                mish_var_dup(mish, &str, &str[v]);
				if (t_error_exist(mish->error))
					break ;
            	v = is_there_a_var(str);
			}
			else
				v = is_there_a_var(&str[v + 1]);
        }
    }
    return (str);
}

char	**mish_substitute_strtab(t_mish *mish, int f(char *, int), char **strtab)
{
	int	i;

	i = 0;
	while (strtab && strtab[i])
	{
		// printf("strtab %d = %s\n", i, strtab[i]); //////
		strtab[i] = mish_substitute_str(mish, f, strtab[i]);
		if (!strtab[i])
			break ;
		i++;
	}
	return (strtab);
}