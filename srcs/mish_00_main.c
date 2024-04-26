/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_00_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:00 by bchene            #+#    #+#             */
/*   Updated: 2024/04/26 21:56:45 by bchene           ###   ########.fr       */
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
		return (2); //exit status qd je fait ls -z
	mish_init(&mish, env);
	
	//mish_print(&mish);
	printf("LOGNAME=%s\n",mish_env_get(&mish, "LOGNAME"));
	printf("NO_ENV=%s\n",mish_env_get(&mish, "NO_ENV"));
	mish_env_add(&mish, "NO_ENV", "SET_ENV");
	printf("NO_ENV=%s\n",mish_env_get(&mish, "NO_ENV"));
	printf("0=%s\n",mish_unset_get(&mish, "0"));
	printf("NO_UNUSET=%s\n",mish_unset_get(&mish, "NO_UNUSET"));
	mish_unset_set(&mish, "NO_UNUSET", "SET_UNUSET");
	printf("NO_UNUSET=%s\n",mish_unset_get(&mish, "NO_UNUSET"));	
	mish_exit_status_set(&mish, "124");
	printf("EXIT_STATUS=%s\n",mish_exit_status_get(&mish));

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

