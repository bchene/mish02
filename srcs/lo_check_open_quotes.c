/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_check_open_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:54:49 by locharve          #+#    #+#             */
/*   Updated: 2024/06/04 15:53:15 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

int	mish_check_open_quotes(t_mish *mish)
{
	int		i;
	char	q;

	i = 0;
	q = 0;
	while (mish->line && mish->line[i])
	{
		if (mish->line[i] == '\'' || mish->line[i] == '\"')
		{
			q = mish->line[i];
			i++;
			while (mish->line[i] && mish->line[i] != q)
				i++;
			if (!mish->line[i])
			{
				if (q == '\'')
					return (mish_error_add(mish, err_quote_open, errno, NULL));
				else if (q == '\"')
					return (mish_error_add(mish, err_dquote_open, errno, NULL));
			}
		}
		i++;
	}
	return (0);
}
