/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_73_builtin_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 15:59:25 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"
#include "limits.h"

/* pwd with no options */
void	builtin_pwd(t_process *process)
{
	char	*pwd;

	if (t_process_is_invalid_option(process))
		return ;
	pwd = malloc(1024 * sizeof(char));
	getcwd(pwd, 1024);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		process->exitstatus = 0;
	}
	else
		mish_error_add(process->mish, err_malloc, errno, "builtin_pwd");
}
