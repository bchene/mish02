/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_52_process_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:12 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 18:10:32 by bchene           ###   ########.fr       */
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

	if (ft_strchr(process->av[0], '/'))
	{
		process->cmd = ft_strdup(process->av[0]);
		return (process->cmd);
	}
	i = 0;
	while ((process->mish)->pathlist && ((process->mish)->pathlist)[i])
	{
		str = ft_strjoin(((process->mish)->pathlist)[i], (process->av)[0]);
		if (t_process_cmd_isdir(process, str, (process->av)[0]))
			return (NULL);
		else if (access(str, X_OK) == 0)
		{
			process->cmd = str;
			return (str);
		}
		free(str);
		i++;
	}
	return (str);
}

void	t_process_cmd_setempty(t_process *process, char *cmd)
{
	if (process->av)
		process->av = ft_freesplit(process->av);
	process->av = ft_split(cmd, ' ');
	if (process->av == NULL)
		mish_error_add(process->mish, err_malloc, errno, "cmd_setempty");
	process->ac = 1;
	t_process_cmd_free(process);
}

int	t_process_cmd_isempty(t_process *process)
{
	if (process->av == NULL)
	{
		mish_error_add(process->mish, err_malloc, errno, "process->av == NULL");
		return (0);
	}
	else if ((process->av)[0] == NULL)
	{
		t_process_cmd_setempty(process, "no_cmd");
		return (1);
	}
	else if ((process->av)[0][0] == '\0')
	{
		builtin_error(process, "Command '' not found\n", 127);
		t_process_cmd_setempty(process, "no_cmd");
		return (1);
	}	
	return (0);
}

int	t_process_cmd_isbuiltin(t_process *process)
{
	char	*cmd;

	cmd = (process->av)[0];
	if (!ft_strcmp(cmd, "."))
		builtin_error(process, "minishell: .: filename argument required", 2);
	if ((process->av)[0] == NULL || !ft_strcmp(cmd, "echo") \
	|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") \
	|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") \
	|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit") \
	|| !ft_strcmp(cmd, "pmish") || !ft_strcmp(cmd, "pes") \
	|| !ft_strcmp(cmd, "."))
	{
		t_process_cmd_free(process);
		return (1);
	}
	return (0);
}
