/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_02_prompt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/04/27 14:47:54 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	mish_prompt(t_mish *mish)
{
	if (mish->prompt == NULL)
		mish_prompt_begin(mish);
	else
	{
		add_history(mish->line);
		if (mish->line)
			free(mish->line);
		free(mish->prompt);
		mish_prompt_set(mish);
	}
	if (mish->prompt == NULL)
		mish_error_add(mish, err_malloc, errno, "mish->prompt is NULL");
	else
	{
		printf("%s", mish->prompt);
		mish->line = readline(mish->prompt);
	}
}

void	mish_prompt_set(t_mish *mish)
{
	char	*session_m;

	session_m = getenv("SESSION_MANAGER");
	session_m = ft_strchr(session_m, '/');
	session_m = ft_strndup(session_m + 1, ft_strchr(session_m, '.') - (session_m + 1));
	if (!session_m)
		return ;
	mish->prompt = ft_strjoin_va("", "\001\e[1;36m\002\001\e[40m\002", getenv("LOGNAME"), 
	"\001\e[0;35m\002\001\e[40m\002"," @", session_m, " ", 
	"\001\e[0;34m\002\001\e[40m\002", ft_strnrchr(getenv("PWD"), 2, '/'), "/", 
	"\001\e[0m\002 $>", NULL);
	free(session_m);
	return ;
}

/*
static void	mish_setprompt(t_mish *mish)
{
	mish->prompt = ft_strjoin(mish->prompt, "\033[0;31m:>user");
}
*/

void	mish_prompt_begin(t_mish *mish)
{
	mish->prompt = ft_strjoin("\001\e[0;31m\002:::::::::::::::::::::>MINISHELL \n\
\001\e[0;32m\002::::::::::::::::::>MINISHELL \n\
\001\e[0;33m\002:::::::::::::::>MINISHELL \n\
\001\e[0;34m\002::::::::::::>MINISHELL \n\
\001\e[0;35m\002:::::::::>MINISHELL \n\
\001\e[0;36m\002::::::>MINISHELL \n", \
	mish->prompt);
}

