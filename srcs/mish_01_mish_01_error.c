/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_01_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:26:04 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 11:57:03 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_err_type	mish_error_add(t_mish *mish, t_err_type t, int en, char *d)
{
	t_error	*new;

	new = t_error_new(t, en, d);
	if (new)
		t_error_add(&(mish->error), new);
	else
		return (err_malloc);
	return (t);
}

static void	mish_error_perror(t_mish *mish, char *str, char *data, int es)
{
	write(2, str, ft_strlen(str));
	if (data)
	{
		write(2, " `", 3);
		write(2, data, ft_strlen(data));
		write(2, "\'\n", 3);
	}
	mish_exit_status_set(mish, es);
}

void	mish_error_treat(t_mish *mish)
{
	t_error	*error;

	error = mish->error;
	while (error)
	{
		if (err_malloc <= error->type && error->type <= err_fork)
			mish_error_print(error->err_no, error->data);
		else if (error->type == err_quote_open)
			mish_error_perror(mish, \
			"minishell: syntax error \' not closed\n", NULL, 2);
		else if (error->type == err_dquote_open)
			mish_error_perror(mish, \
			"minishell: syntax error \" not closed\n", NULL, 2);
		else if (error->type == err_token_unexpected)
			mish_error_perror(mish, \
			"minishell: syntax error near unexpected token", error->data, 2);
		else if (error->type == err_unhandled)
			mish_error_perror(mish, \
			"minishell: syntax error near unhandled token", error->data, 2);
		error = error->next;
	}
}

void	mish_error_treat_exit(t_mish *mish)
{
	t_error	*error;

	error = mish->error;
	while (error)
	{
		if (error->type == err_exit)
			return ;
		error = error->next;
	}
	t_error_lst_free(&(mish->error));
}
