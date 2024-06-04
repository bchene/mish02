/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:42:16 by locharve          #+#    #+#             */
/*   Updated: 2024/06/04 17:22:20 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

int	g_signal;

static void	prompt_sigint(int signal)
{
	g_signal = signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
}

static void	heredoc_sigint(int signal)
{
	char	c;

	g_signal = signal;
	c = '\n';
	ioctl(0, TIOCSTI, &c);
	rl_on_new_line();
	rl_replace_line("", 0);
}

static void	exec_sigint(int signal)
{
	g_signal = signal;
}

void	handler_set_type(t_handeler_type type)
{
	if (type == handler_prompt)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &prompt_sigint);
	}
	else if (type == handler_heredoc)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &heredoc_sigint);
	}
	else if (type == handler_exec)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &exec_sigint);
	}
	else if (type == handler_default)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
