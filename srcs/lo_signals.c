/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:42:16 by locharve          #+#    #+#             */
/*   Updated: 2024/06/03 21:47:41 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

// Ctrl-D	-> EOF si dans heredoc, exit si la line est vide
//			-> si dans heredoc, p.e "cat << limit (...) oui\n Ctrl-D : cat "limit" 
//			-> contrairement a Ctrl-C

int	g_signal;

void	prompt_sigint(int signal)
{
	g_signal = signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
}

void	heredoc_sigint(int signal)
{
	char	c;

	g_signal = signal;
	c = '\n';
	ioctl(0, TIOCSTI, &c);
	rl_on_new_line();
	rl_replace_line("", 0);
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
	else if(type == handler_default)
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

/*
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

void	heredoc_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;

	// char	c;

	// g_sig = sig;
	// c = '\n';
	// ioctl(0, TIOCSTI, &c);
	// rl_on_new_line();
	// rl_replace_line("", 0);


	if (sig == SIGINT)
	{
		g_signal = sig;
		fprintf(stderr, "heredoc_handler 0 SIGINT\n"); //TEST
		if (info->si_pid)
		{
			ioctl()
			rl_replace_line("", 0);
			rl_on_new_line();
			//rl_redisplay();
			close(0);
			fprintf(stderr, "heredoc_handler 1 SIGINT\n"); //TEST
		}
	}
}

void	no_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) info;
	(void) ucontext;

	//g_signal = sig;
	if (sig == SIGINT)
		return ;
	if (sig == SIGQUIT)
		return ;	
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
*/