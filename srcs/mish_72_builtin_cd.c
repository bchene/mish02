/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_72_builtin_cd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:20:10 by bchene            #+#    #+#             */
/*   Updated: 2024/05/22 16:09:57 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

/* cd with only a relative or absolute path */
void	builtin_cd(t_process *process)
{
	if (process->ac == 1)
		return ;	//home
	if (process->ac == 2)
	{
		mish_cd(process);
	}
	else
		builtin_error(process, "minishell: cd: too many arguments\n", 2);
}

void	mish_cd(t_process *p)
{
	char		*pwd;

	if (p->av[1][0] != '/')
	{
		p->av[1] = ft_strjointoleft(p->av[1], "/");
		p->av[1] = \
		ft_strjointoleft(p->av[1], mish_env_get(p->mish, "PWD"));
	}
	if (chdir(p->av[1]))
		builtin_perror(p, errno, p->av[1], 1);
	else
	{
		pwd = malloc(1024 * sizeof(char));
		getcwd(pwd, 1024);
		mish_env_set(p->mish, "OLDPWD", mish_env_get(p->mish, "PWD"));
		mish_env_set(p->mish, "PWD", pwd);
		free(pwd);
		mish_exit_status_set(p->mish, 0);
	}
}
