/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_90_ft3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:29:31 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 16:37:07 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	ft_sort_split(char **split)
{
	int		i;
	int		size;

	size = ft_splitsize(split);
	while (size > 1)
	{
		i = 0;
		while (++i < size)
		{
			if (ft_strcmp(split[i], split[i - 1]) < 0)
				ft_strswap(split + i, split + i - 1);
		}
		size--;
	}
}
