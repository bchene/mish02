/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_03_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 12:46:08 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_err_type	mish_line_parse(t_mish *mish)
{
	if (mish_check_line(mish))
		return (t_error_exist(mish->error));
	mish->splitline = mish_split(mish->line, '|');
	mish->nb = ft_splitsize(mish->splitline);
	if (mish->splitline == NULL)
		return (mish_error_add(mish, err_malloc, errno, "splitline == NULL"));
	if (mish_path_set(mish))
		return (t_error_exist(mish->error));
	if (mish_fds_malloc(mish))
		return (t_error_exist(mish->error));
	if (mish_pid_malloc(mish))
		return (t_error_exist(mish->error));
	if (mish_p_malloc(mish))
		return (t_error_exist(mish->error));
	return (0);
}
