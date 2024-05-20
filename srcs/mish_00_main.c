/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_00_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:00 by bchene            #+#    #+#             */
/*   Updated: 2024/05/20 19:46:54 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

int	g_signal;

int	mish_continue(t_mish *mish)
{
	if (mish_exit_status_get(mish) == 42)
	{
		return (0);
	}
	else if (t_error_exist(mish->error))
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
		if (mish_continue(&mish) && mish.line && mish.line[0])
			mish_line_parse(&mish); // check>split>feed mish
		if (mish_continue(&mish) && mish.line && mish.line[0])
			mish_p_parse(&mish); // parse>feed process	
		if (mish_continue(&mish) && mish.line && mish.line[0])
			mish_exec(&mish);
		mish_error_treat(&mish);
		mish_error_treat_exit(&mish);
		if (mish_continue(&mish) && mish.line && mish.line[0])
			mish_reset(&mish);
	}
	mish_free(&mish, 1);
	return (mish.nb);
}
