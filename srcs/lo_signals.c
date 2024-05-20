/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:42:16 by locharve          #+#    #+#             */
/*   Updated: 2024/05/20 17:34:01 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "mish.h"

// Ctrl-D	-> EOF si dans heredoc, exit si la line est vide
//			-> si dans heredoc, p.e "cat << limit (...) oui\n Ctrl-D : cat "limit" 
//			-> contrairement a Ctrl-C

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
/*
int	g_signal;

static void	sigint_action(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_signal(int sig)
{
	g_signal = sig;
	if (g_signal == SIGINT)
		sigint_action();
	return ;
}

//static void	signals_action(t_mish *mish);

int	main(void)
{
	struct sigaction	sa;
	char				*line;

	bzero(&sa, sizeof(sa));
	sa.sa_handler = &handle_signal;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	line = readline("$> ");
	while (line)
	{
		printf("--- line received\n");
		free(line);
		line = readline("$> ");
	}
	return (0);
}
*/
