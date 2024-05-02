/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_00_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:00 by bchene            #+#    #+#             */
/*   Updated: 2024/05/02 19:10:14 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

int	g_signal;

t_err_type	mish_parse_line(t_mish *mish)
{
	return (t_error_exist(mish->error));
}
t_err_type	mish_parse_process_line(t_mish *mish)
{
	return (t_error_exist(mish->error));
}
t_err_type	mish_pipex(t_mish *mish)
{
	return (t_error_exist(mish->error));
}

int		mish_continue(t_mish *mish)
{
	if(mish_exit_status_get(mish) == 42)
	{
		return (0);
	}
	if (t_error_exist(mish->error))
	{
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_mish	mish;

	(void) argv;
	if (argc != 1)
		return (2); //exit status qd je fait ls -z
	mish_init(&mish, env);
	while (mish_continue(&mish))
	{
		mish_prompt(&mish);
		mish_error_add(&mish, err_other, errno, "TEST"); // TEST 
		if (mish_continue(&mish))
			mish_parse_line(&mish);
		if (mish_continue(&mish))
			mish_parse_process_line(&mish);
		if (mish_continue(&mish))
			mish_pipex(&mish);
	}
	// main_test_env(&mish); 		// TEST
	main_test_set_process(&mish); 	// TEST
	mish.nb = mish_exit_status_get(&mish);
	mish_free(&mish);
	rl_clear_history();
	return (mish.nb);
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

