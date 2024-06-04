/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_check_syntax_error2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:54:13 by locharve          #+#    #+#             */
/*   Updated: 2024/06/04 15:55:44 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

static int	mish_check_unexpected(t_mish *mish, char *str, char *curr_t)
{
	char	*next_t;

	if (mish && str && curr_t)
	{
		if (curr_t[0] == '|' && is_first_tkn(mish->line, str))
		{
			mish_set_unexpected_error(mish, curr_t, "|");
			return (t_error_exist(mish->error));
		}
		next_t = token_dup(&str[ft_strlen(curr_t) + \
				ft_strlen_while(&str[ft_strlen(curr_t)], ft_isspace)]);
		if (next_t)
		{
			if (!*next_t || is_in_str("|<>", *next_t))
				mish_set_unexpected_error(mish, curr_t, next_t);
			free(next_t);
		}
	}
	return (t_error_exist(mish->error));
}

int	mish_check_syntax_error(t_mish *mish)
{
	char	*curr_t;
	int		i;

	i = 0;
	while (mish && mish->line && mish->line[i])
	{
		if (is_in_str("|<>", mish->line[i]) \
				&& !is_between_quotes(mish->line, i) \
				&& !t_error_exist(mish->error))
		{
			curr_t = token_dup(&mish->line[i]);
			if (curr_t)
			{
				mish_check_unexpected(mish, &mish->line[i], curr_t);
				i += ft_strlen(curr_t);
				free(curr_t);
			}
			else
				return (mish_error_add(mish, err_malloc,
						errno, "mish_check_syntax_error"));
		}
		else
			i++;
	}
	return (t_error_exist(mish->error));
}
