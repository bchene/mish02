/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_91_ft_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:29:31 by bchene            #+#    #+#             */
/*   Updated: 2024/05/16 17:34:57 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

int	is_alphanum_underscore(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	else
		return (0);
}

size_t	ft_strlen_while(char *str, int f(char))
{
	size_t	i;

	i = 0;
	while (str && str[i] && f(str[i]))
		i++;
	return (i);
}

// on peut utiliser ft_getnbsplit car utiliser pour le split
/*
int	char_count(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
*/

// equivaux a ft_freesplit ?
void	strtab_free(char **strtab)
{
	int	i;

	i = 0;
	if (strtab)
	{
		while (strtab[i])
		{
			free(strtab[i]);
			i++;
		}
		free(strtab);
	}
	return ;
}
