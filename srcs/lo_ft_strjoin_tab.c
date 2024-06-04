/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_ft_strjoin_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:13:21 by bchene            #+#    #+#             */
/*   Updated: 2024/06/04 16:13:49 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

size_t	ft_strlen_tab(char **strtab)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (strtab[i])
	{
		len += ft_strlen(strtab[i]);
		i++;
	}
	return (len);
}

char	*ft_strcpy_tab(char *dst, char **srcs, char sep)
{
	unsigned int	i;
	size_t			end;

	end = 0;
	i = 0;
	while (srcs[i])
	{
		ft_strcpy(&dst[end], srcs[i]);
		end = ft_strlen(dst);
		if (sep && srcs[i + 1])
		{
			dst[end] = sep;
			end++;
		}
		i++;
	}
	return (dst);
}

char	*ft_strjoin_tab(char **strtab, char sep)
{
	char	*dst;
	size_t	len;
	size_t	split_size;

	len = ft_strlen_tab(strtab);
	split_size = ft_splitsize(strtab);
	if (sep && split_size > 1)
		len += split_size - 1;
	dst = ft_calloc(len + 1, sizeof(char));
	if (dst)
		dst = ft_strcpy_tab(dst, strtab, sep);
	return (dst);
}
