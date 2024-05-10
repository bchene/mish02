/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_00_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:00 by bchene            #+#    #+#             */
/*   Updated: 2024/05/10 15:12:32 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

int	g_signal;

t_err_type	mish_parse_line(t_mish *mish)
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
		//mish_error_add(&mish, err_other, errno, "TEST"); // TEST 
		
		// new BEN
		if (mish_continue(&mish))
			mish_line_parse(&mish);				// check>split>feed mish
		
		// new BEN
		if (mish_continue(&mish))
			mish_p_parse(&mish);				// parse>feed process
		
		// mish_print(&mish);

		if (mish_fork_parent(&mish))
			return (t_error_exist(mish.error));

		//gestion des erreurs
		mish_reset(&mish);
	}
	mish_free(&mish);
	return (mish.nb);
}
