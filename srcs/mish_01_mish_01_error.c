/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_01_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:26:04 by bchene            #+#    #+#             */
/*   Updated: 2024/05/13 20:21:44 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

// si erreur de malloc dans erreur comment sortir
t_err_type	mish_error_add(t_mish *mish, t_err_type t, int en, char *d)
{
	t_error	*new;

	new = t_error_new(t, en, d);
	if (new)
		t_error_add(&(mish->error), new);
	else
		return (err_malloc);
	return (t);
}

void	mish_error_print(int en, char *str)
{
	write(2, "minishell: ", 11);
	if (str)
	{
		write(2, str, ft_strlen(str));
		if (ft_strlen(strerror(en)))
			write(2, " :", 2);
	}
	if (ft_strlen(strerror(en)))
		write(2, strerror(en), ft_strlen(strerror(en)));
	write(2, "\n", 1);
}
