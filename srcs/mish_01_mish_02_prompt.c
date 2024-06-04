/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_02_prompt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/06/04 13:23:51 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

static void	mish_prompt_set(t_mish *mi)
{
	char	*str;

	mi->prompt = ft_strempty(NULL);
	if (mi->prompt && ft_strlen(mish_env_get(mi, "LOGNAME")))
	{
		mi->prompt = ft_strjointo(mi->prompt, "\001\e[0;32m\002");
		mi->prompt = ft_strjointo(mi->prompt, mish_env_get(mi, "LOGNAME"));
	}
	if (mi->prompt && ft_strlen(mish_env_get(mi, "SESSION_MANAGER")))
	{
		str = mish_env_get(mi, "SESSION_MANAGER");
		str = ft_strchr(str, '/');
		str = ft_strndup(str + 1, ft_strchr(str, '.') - (str + 1));
		mi->prompt = ft_strjointo(mi->prompt, "\001\e[2;32m\002 @");
		mi->prompt = ft_strjointo(mi->prompt, str);
		free (str);
	}
	if (mi->prompt && ft_strlen(mish_env_get(mi, "PWD")))
	{
		mi->prompt = ft_strjointo(mi->prompt, "\001\e[0;32m\002 ");
		mi->prompt = ft_strjointo(mi->prompt, \
		ft_strnrchr(mish_env_get(mi, "PWD"), 1, '/') + 1);
		mi->prompt = ft_strjointo(mi->prompt, "/");
	}
	mi->prompt = ft_strjointo(mi->prompt, "\001\e[0m\002 $ ");
}

/*
	CTRLC
	if (g_signal == SIGINT)
		mettre exit stat a 128 + SIGINT = 130
		mettre g_dignal = 0
		affchie "^C\n" a priori rien a ajouter.
*/

void	mish_prompt(t_mish *mish)
{
	if (mish->line)
	{
		if (ft_strlen(mish->line) > 0)
			add_history(mish->line);
		ft_strfree(&(mish->line));
	}
	free(mish->prompt);
	mish_prompt_set(mish);
	if (mish->prompt == NULL)
		mish_error_add(mish, err_malloc, errno, "mish->prompt is NULL");
	else
	{
		handler_set_type(handler_prompt);
		mish->line = readline(mish->prompt);
		if (g_signal == SIGINT)
		{
			mish_exit_status_set(mish, 130);
			g_signal = 0;
		}
		if (mish->line == NULL)
			mish->line = ft_strjoinva("exit", " ", "$?", NULL);
		handler_set_type(handler_ignore);
	}
}

/* https://patorjk.com/software/taag/#p=display&f=Graffiti&t=minishell */
/*
static void	mish_prompt_start(t_mish *mish)
{
	char	*str;

	mish->prompt = ft_strempty(mish->prompt);
	str = ft_strjoinva("", \
"\001\e[0;32m\002", \
"              d8b          d8b          888               888 888\n", \
"              Y8P          Y8P          888               888 888\n", \
"                                        888               888 888\n", \
"88888b.d88b.  888 88888b.  888 .d8888b  88888b.   .d88b.  888 888\n", \
"888 \"888 \"88b 888 888 \"88b 888 88K      888 \"88b d8P  Y8b 888 888\n", \
"888  888  888 888 888  888 888 \"Y8888b. 888  888 88888888 888 888\n", \
"888  888  888 888 888  888 888      X88 888  888 Y8b.     888 888\n", \
"888  888  888 888 888  888 888  88888P' 888  888  \"Y8888  888 888\n", \
"\001\e[2;32m\002\n", \
"                                   Louis Charvet & Benjamin Chêne\n\n", \
	NULL);
	if (str)
	{
		printf("%s", str);
		free(str);
	}
	else
		mish_error_add(mish, err_malloc, errno, "malloc mish_prompt_start");
}
*/