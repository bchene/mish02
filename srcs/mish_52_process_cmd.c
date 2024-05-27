/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_52_process_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:12 by bchene            #+#    #+#             */
/*   Updated: 2024/05/27 21:47:56 by bchene           ###   ########.fr       */
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
		return(0);
	}
	else if ((process->av)[0] == NULL || (process->av)[0][0] == '\0')
	{
		t_process_cmd_setempty(process, "no_cmd");
		return (1);
	}
	// A TESTER
	/*
	else if (!ft_strcmp((process->av)[0], "\"\"") \
	|| !ft_strcmp((process->av)[0], "\'\'"))
	{
		if (!ft_strcmp((process->av)[0], "\"\""))
			write(2 ,"\"\": command not found\n" , 23);
		else if (!ft_strcmp((process->av)[0], "\'\'"))
			write(2 ,"\'\': command not found\n" , 23);
		return (0);
	}
	*/
	return (0);
}

int	t_process_cmd_isbuiltin(t_process *process)
{
	char *cmd;

	cmd = (process->av)[0];
	if ( (process->av)[0] == NULL || !ft_strcmp(cmd, "echo") \
	|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") \
	|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") \
	|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit") \
	|| !ft_strcmp(cmd, "pmish") || !ft_strcmp(cmd, "pes"))
	{
		t_process_cmd_free(process);
		return (1);
	}
	// else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1))
	// {
	// 	if (process->mish->nb == 1)
	// 		mish_error_add(process->mish, err_exit, 0, "exit");
	// 	t_process_cmd_setempty(process);
	// 	return (2);
	// }
	return (0);
}

int t_process_cmd_isdir(t_process *process, char *path, char *cmd) 
{
	struct stat stats;

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
