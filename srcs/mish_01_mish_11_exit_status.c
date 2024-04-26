/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_11_exit_status.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/04/26 19:37:10 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	mish_exit_status_set(t_mish *mish, char *value)
{
	mish_unset_set(mish, "?", value);
}

char	*mish_exit_status_get(t_mish *mish)
{
	char *exit_status;

	exit_status = mish_unset_get(mish, "?");
	return (exit_status);
}
