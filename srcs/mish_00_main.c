/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_00_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:00 by bchene            #+#    #+#             */
/*   Updated: 2024/04/26 17:31:30 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

// const static int	g_signal;

int	main(int argc, char **argv, char **env)
{
	t_mish	mish;
	int		exit_status;

	exit_status = 0;
	if (argc != 1)
		return (1); //mettre le num de l erreur syntaxe error
	mish_init(&mish, env);
	mish_print(&mish);
	mish_free(&mish);
	return (exit_status);
	(void) argv;
}

/* 24/04/24 					*/
/* Louis						*/
/* main pour tester le parsing 	*/
/*
int	main(int argc, char **argv, char **env)
{
	t_mish	mish;

	//mish_arg_check();
	// gestion si argc != 1
	mish_init(&mish, env);
	if (argc == 2)
	{
		mish.line = ft_strdup(argv[1]);
		if (mish.line && mish_parsing(&mish))
		{
			mish_print_processes_free(&mish); ///
			t_error_lst_free(&mish.error);
			free(mish.line);
		}
	}
	return (0);
}
*/

