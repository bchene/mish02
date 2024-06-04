/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_substitute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:45:56 by locharve          #+#    #+#             */
/*   Updated: 2024/06/04 16:36:59 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

char	*copy_sub(char *dst, char *src, char *var, char *sub)
{
	char	*var_addr;
	char	*tmp;
	size_t	len_var;
	size_t	step;

	var_addr = ft_strchr(src, '$');
	len_var = ft_strlen(var);
	while (is_between_quotes(src, var_addr - src) == 1 \
			|| ft_strncmp(var_addr, var, len_var))
		var_addr = ft_strchr(var_addr + 1, '$');
	tmp = ft_strdup(&var_addr[len_var]);
	if (tmp)
	{
		ft_strncpy(dst, src, var_addr - src);
		step = ft_strlen(dst);
		ft_strcpy(&dst[step], sub);
		step = ft_strlen(dst);
		ft_strcpy(&dst[step], tmp);
		free(tmp);
	}
	return (dst);
}

char	*dup_substituting(char *src, char *var, char *sub)
{
	char	*dst;

	dst = ft_calloc(ft_strlen(src) - ft_strlen(var)
			+ ft_strlen(sub) + 1, sizeof(char));
	if (dst)
	{
		dst = copy_sub(dst, src, var, sub);
		free(src);
	}
	return (dst);
}

char	*substitute_var(t_mish *mish, char *src, char *var)
{
	char	*dst;
	char	*sub;

	dst = NULL;
	sub = get_var_value(mish, var);
	if (sub)
	{
		dst = dup_substituting(src, var, sub);
		if (!dst)
			mish_error_add(mish, err_malloc, errno, "substitute_var");
		free(sub);
	}
	else
		mish_error_add(mish, err_malloc, errno, "substitute_var");
	return (dst);
}
