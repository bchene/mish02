/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_00_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:00 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 12:00:23 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

int	mish_continue(t_mish *mish)
{
	if (t_error_exist(mish->error))
	{
		return (0);
	}
	return (1);
}

static void	mish_exit_arg(char **argv)
{
	if (argv && argv[1] && argv[1][0] == '-' && ft_isalpha(argv[1][1]))
	{
		write(2, "minishell :too many options\n", 29);
		exit (2);
	}
	else
		write(2, "minishell :too many arguments\n", 31);
	exit (1);
}

int	main(int argc, char **argv, char **env)
{
	t_mish	mish;

	if (argc > 1)
		mish_exit_arg(argv);
	mish_init(&mish, env);
	while (mish_continue(&mish))
	{
		mish_prompt(&mish);
		if (mish_continue(&mish) && mish.line && mish.line[0])
			mish_line_parse(&mish);
		if (mish_continue(&mish) && mish.line && mish.line[0])
			mish_p_parse(&mish);
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
