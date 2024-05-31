/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:42:16 by locharve          #+#    #+#             */
/*   Updated: 2024/05/31 17:09:58 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

// Ctrl-D	-> EOF si dans heredoc, exit si la line est vide
//			-> si dans heredoc, p.e "cat << limit (...) oui\n Ctrl-D : cat "limit" 
//			-> contrairement a Ctrl-C

int	g_signal;

void	init_sa(t_sa *sa, void handler(int, siginfo_t *, void *))
{
	sa->sa_sigaction = handler;
	sa->sa_flags = SA_SIGINFO;
	//signal(SIGINT, SIG_IGN); // test
	sigaction(SIGINT, sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	//sigaction(SIGQUIT, sa, NULL);
}

static void	sigint_action(int pid)
{
	write(1, "\n", 1);
	if (pid)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	sigquit_action(int pid)
{
	if (!pid) ////
	{
		write(1, "Quit (core dumped)\n", 20);
	}
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;

	g_signal = sig;
	//printf("\ng_signal = %d\n", g_signal);
	if (g_signal == SIGINT)
		sigint_action(info->si_pid);
	else if (g_signal == SIGQUIT)
		sigquit_action(info->si_pid);
	return ;
}