/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_52_process_cmd2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:12 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 13:47:39 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

int	t_process_cmd_isdir(t_process *process, char *path, char *cmd)
{
	struct stat	stats;

	if (stat(path, &stats) == 0)
	{
		if (S_ISDIR(stats.st_mode))
		{
			if (process->exitstatus == 0)
			{
				write(2, "minishell :", 12);
				write(2, cmd, ft_strlen(cmd));
				write(2, " : is a directory\n", 19);
				process->exitstatus = 127;
			}
			if (path)
				free(path);
			return (1);
		}
	}
	return (0);
}
