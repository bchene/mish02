/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:42:16 by locharve          #+#    #+#             */
/*   Updated: 2024/05/13 14:15:31 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

// Ctrl-D	-> EOF si dans heredoc, exit si la line est vide
//			-> si dans heredoc, p.e "cat << limit (...) oui\n Ctrl-D : cat "limit" 
//			-> contrairement a Ctrl-C

// int	g_signal;
/*
static void	handle_signal(int sig)
{
	if (sig == SIGINT)
}
*/
