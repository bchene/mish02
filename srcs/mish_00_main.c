/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_00_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:00 by bchene            #+#    #+#             */
/*   Updated: 2024/04/25 21:03:13 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

// const static int	g_signal;

/* main pour tester le parsing */
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

