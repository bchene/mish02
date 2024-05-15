/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_52_process_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:12 by bchene            #+#    #+#             */
/*   Updated: 2024/05/15 17:28:12 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	t_process_cmd_free(t_process *process)
{
	if (process->cmd)
	{
		free(process->cmd);
		process->cmd = NULL;
	}
}

char	*t_process_cmd_get(t_process *process)
{
	int		i;
	char	*str;
	char	**path;

	path = (process->mish)->pathlist;
	i = 0;
	while (path && path[i])
	{
		str = ft_strjoin(path[i], (process->av)[0]);
		if (access(str, X_OK) == 0)
		{
			process->cmd = str;
			return (str);
		}
		free(str);
		i++;
	}
	str = ft_strdup((process->av)[0]);
	process->cmd = str;
	return (str);
}

void	t_process_cmd_setempty(t_process *process)
{
	if (process->av)
		process->av = ft_freesplit(process->av);
	process->av = ft_split("empty_cmd", ' ');
	if (process->av == NULL)
		mish_error_add(process->mish, err_malloc, errno, "empty_cmd");
	process->ac = 1;
	t_process_cmd_free(process);	
}

int	t_process_cmd_isempty(t_process *process)
{
	/* gerer le cas chaine vide "" differement */
	/* fprintf(stderr,"t_process_cmd_isempty av=%p av[0]=%p\n",
	 process->av, process->av[0]); */
	if (!process->av || !(process->av)[0] || process->ac == 0)
	{
		t_process_cmd_setempty(process);
		return (1);
	}
	else if (!ft_strncmp((process->av)[0], "\"\"", 3) \
	|| !ft_strncmp((process->av)[0], "\'\'", 3))
	{
		free((process->av)[0]);
		(process->av)[0] = ft_strdup("\0");
		t_process_cmd_free(process);
		process->cmd = ft_strdup("\0");
	}
	return (0);
}

int	t_process_cmd_isbuiltin(t_process *process)
{
	char *cmd;

	cmd = (process->av)[0];
	if (!ft_strncmp(cmd, "echoTEST", ft_strlen(cmd) + 1) \
	|| !ft_strncmp(cmd, "cdTEST", ft_strlen(cmd) + 1) \
	|| !ft_strncmp(cmd, "pwdTEST", ft_strlen(cmd) + 1) \
	|| !ft_strncmp(cmd, "exportTEST", ft_strlen(cmd) + 1) \
	|| !ft_strncmp(cmd, "unsetTEST", ft_strlen(cmd) + 1) \
	|| !ft_strncmp(cmd, "env", ft_strlen(cmd) + 1) \
	|| !ft_strncmp(cmd, "pmish", ft_strlen(cmd) + 1))
	{
		t_process_cmd_free(process);
		return (1);
	}
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1))
	{
		if (process->mish->nb == 1)
			mish_error_add(process->mish, err_exit, 0, "exit");
		t_process_cmd_setempty(process);
		return (2);
	}
	return (0);
}
