/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_02_prompt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/09 15:33:41 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	mish_prompt(t_mish *mish)
{
	if (mish->prompt == NULL)
	{
		mish_prompt_start2(mish);
		mish->prompt = ft_strempty(mish->prompt);
		mish_prompt(mish);
		return ;
	}
	else
	{
		if (mish->line)
		{
			add_history(mish->line);
			if (mish->line)
				ft_strfree(&(mish->line));
		}
		free(mish->prompt);
		mish_prompt_set(mish);
	}
	if (mish->prompt == NULL)
		mish_error_add(mish, err_malloc, errno, "mish->prompt is NULL");
	else
	{
		mish->line = readline(mish->prompt);
	}
}

void	mish_prompt_set(t_mish *mish)
{
	char *str;

	mish->prompt = ft_strempty(NULL);
	if (mish->prompt && ft_strlen(mish_env_get(mish, "LOGNAME")))
	{
		mish->prompt = ft_strjointo(mish->prompt, "\001\e[0;32m\002");
		mish->prompt = ft_strjointo(mish->prompt, mish_env_get(mish, "LOGNAME"));
	}
	if (mish->prompt && ft_strlen(mish_env_get(mish, "SESSION_MANAGER")))
	{
		str = mish_env_get(mish, "SESSION_MANAGER");
		str = ft_strchr(str, '/');
		str = ft_strndup(str + 1, ft_strchr(str, '.') - (str + 1));
		mish->prompt = ft_strjointo(mish->prompt, "\001\e[2;32m\002 @");
		mish->prompt = ft_strjointo(mish->prompt, str);
		free (str);
	}
	if (mish->prompt && ft_strlen(mish_env_get(mish, "PWD")))
	{
		mish->prompt = ft_strjointo(mish->prompt, "\001\e[0;32m\002 ");
		mish->prompt = ft_strjointo(mish->prompt, ft_strnrchr(mish_env_get(mish, "PWD"), 1, '/') + 1);
		mish->prompt = ft_strjointo(mish->prompt, "/");
	}
	mish->prompt = ft_strjointo(mish->prompt, "\001\e[0m\002 $>");
}

/* https://patorjk.com/software/taag/#p=display&f=Graffiti&t=minishell */
void	mish_prompt_start(t_mish *mish)
{
	char *str;

	str = ft_strjoin_va("", \
	"\001\e[0;32m\002", 
	"        .__       .__       .__           .__  .__   \n",
	"  _____ |__| ____ |__| _____|  |__   ____ |  | |  |  \n",
	" /     \\|  |/    \\|  |/  ___/  |  \\_/ __ \\|  | |  |  \n",
	"|  Y Y  \\  |   |  \\  |\\___ \\|   Y  \\  ___/|  |_|  |__\n",
	"|__|_|  /__|___|  /__/____  >___|  /\\___  >____/____/\n",
	"      \\/        \\/        \\/     \\/     \\/           \n",
	"\001\e[0;32m\002", 
	"                       Louis Charvet & Benjamin Chêne\n\n\n",	
	NULL);
	if (str)
	{
		printf("%s", str);
		free(str);		
	}
	else
		mish_error_add(mish, err_malloc, errno, "malloc mish_prompt_start");
}

void	mish_prompt_start2(t_mish *mish)
{
	char *str;

	str = ft_strjoin_va("", \
"\001\e[0;32m\002", \
"              d8b          d8b          888               888 888\n", 
"              Y8P          Y8P          888               888 888\n", 
"                                        888               888 888\n", 
"88888b.d88b.  888 88888b.  888 .d8888b  88888b.   .d88b.  888 888\n",  
"888 \"888 \"88b 888 888 \"88b 888 88K      888 \"88b d8P  Y8b 888 888\n",  
"888  888  888 888 888  888 888 \"Y8888b. 888  888 88888888 888 888\n", 
"888  888  888 888 888  888 888      X88 888  888 Y8b.     888 888\n",  
"888  888  888 888 888  888 888  88888P' 888  888  \"Y8888  888 888\n", 
"\001\e[2;32m\002\n", 
"                                   Louis Charvet & Benjamin Chêne\n\n", 
	NULL);
	if (str)
	{
		printf("%s", str);
		free(str);		
	}
	else
		mish_error_add(mish, err_malloc, errno, "malloc mish_prompt_start");
}

