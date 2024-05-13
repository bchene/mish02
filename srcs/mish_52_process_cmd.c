/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_52_process_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:12 by bchene            #+#    #+#             */
/*   Updated: 2024/05/13 19:17:10 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

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

int	t_process_cmd_isempty(t_process *process)
{
	//fprintf(stderr,"t_process_cmd_isempty av=%p av[0]=%p\n", process->av, process->av[0]);
	if (!process->av || !(process->av)[0] || process->ac == 0)
	{
		if(process->av)
			process->av = ft_freesplit(process->av);
		process->av = ft_split("empty_function",' ');
		process->ac = 1;
		if(process->cmd)
		{
			free(process->cmd);
			process->cmd = NULL;
		}
		return (1);
	}
	return (0);
}

int	t_process_cmd_isbuiltin(t_process *process)
{
	if (!ft_strncmp((process->av)[0], "echoTEST", ft_strlen("echoTEST"))
	|| !ft_strncmp((process->av)[0], "cdTEST", ft_strlen("cdTEST"))
	|| !ft_strncmp((process->av)[0], "pwdTEST", ft_strlen("pwdTEST"))
	|| !ft_strncmp((process->av)[0], "exportTEST", ft_strlen("exportTEST"))
	|| !ft_strncmp((process->av)[0], "unsetTEST", ft_strlen("unsetTEST"))
	|| !ft_strncmp((process->av)[0], "envTEST", ft_strlen("envTEST")))
	{
		fprintf(stderr,"t_process_cmd_isbuiltin : %s\n", (process->av)[0]);
		if(process->cmd)
		{
			free(process->cmd);
			process->cmd = NULL;
		}
		return (1);
	}
	else if (!ft_strncmp((process->av)[0], "exit", ft_strlen("exit")))
	{
		// ajouter erreur ou quit ?
		mish_error_add(process->mish, err_exit, 0, "exit");
		return (2);
	}
	return (0);
}
