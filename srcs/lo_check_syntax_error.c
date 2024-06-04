/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_check_syntax_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:54:13 by locharve          #+#    #+#             */
/*   Updated: 2024/06/04 16:10:05 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

static size_t	token_len(char *str)
{
	if (str && *str)
	{
		if (is_in_str("<>", *str))
		{
			if (*str == *(str + 1))
				return (2);
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

char	*token_dup(char *str)
{
	char	*dst;
	size_t	len;

	dst = NULL;
	if (str)
	{
		len = token_len(str);
		dst = strndup(str, len);
	}
	return (dst);
}

int	is_first_tkn(char *line, char *tkn_addr)
{
	size_t	i;

	i = 0;
	while (line + i < tkn_addr && ft_isspace(line[i]))
		i++;
	return (line + i == tkn_addr);
}

void	mish_set_unexpected_error(t_mish *mish, char *curr_t, char *next_t)
{
	if (!ft_strcmp(curr_t, "|"))
	{
		if (!ft_strcmp(next_t, "|"))
			mish_error_add(mish, err_token_unexpected, errno, next_t);
		else if (!*next_t)
			mish_error_add(mish, err_token_unexpected, errno, "newline");
	}
	else if (is_in_str("<>", *curr_t))
	{
		if (!*next_t)
			mish_error_add(mish, err_token_unexpected, errno, "newline");
		else
			mish_error_add(mish, err_token_unexpected, errno, next_t);
	}
	return ;
}
