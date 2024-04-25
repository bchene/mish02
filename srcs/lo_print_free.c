/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_print_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:12:47 by locharve          #+#    #+#             */
/*   Updated: 2024/04/25 21:02:42 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	print_process_lines_free(t_process *p, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (p[i].line)
		{
			printf("p->line:\t%s\n", p[i].line);
			free(p[i].line);
		}
		else
			printf("error\n");
		i++;
	}
	free(p);
	return ;
}

void	print_files_free(t_file *lst)
{
	if (lst)
	{
		printf("line = %s\n", lst->line);
		free(lst->line); ////////
		print_files_free(lst->next);
		free(lst); //////////////
	}
}

void	print_split_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		printf("\t%s\n", split[i]);
		free(split[i]); /////////
		i++;
	}
	free(split);
}

void	mish_print_processes_free(t_mish *mish)
{
	int			i;

	i = 0;
	while (i < mish->nb)
	{
		printf("-------------------- PROCESS %d\n", i);
		printf("line = %s\n", mish->p[i].line);
		printf("ac = %d\n", mish->p[i].ac);
		printf("av =");
		print_split_free(mish->p[i].av);
		printf("---------- INFILES\n");
		print_files_free(mish->p[i].infiles);
		printf("---------- OUTFILES\n");
		print_files_free(mish->p[i].outfiles);

		free(mish->p[i].line);
		i++;
	}
	free(mish->p);
}
/*
void	first_substitution(t_mish *mish, char **line, char *var)
{
	if (var[1] == '0' || var[1] == '?')
		var = ft_strndup(var, 2);
	else
		var = ft_strndup(var, ft_strlen_while(&var[1],
				is_alphanum_underscore) + 1);
	if (!var)
	{
		mish_t_error_add(mish, err_malloc, errno, "first_substitution");
		return; //(NULL);
	}
	*line = substitute_hub(mish, *line, var);
	free(var);
	//return (line);
}
*/
/*
int	main(int argc, char **argv)
{
	t_mish	mish;
	t_error	*head;
	int		i;

	ft_bzero(&mish, sizeof(mish));
	if (argc == 2)
	{
		mish.line = ft_strdup(argv[1]);
		i = is_there_a_var(mish.line);
		if (i)
			mish_var_dup(&mish, &mish.line, &mish.line[i]);
		printf("check_unhandled : %d\nsyntax_error : %d\nopen_quotes : %d\n\n",
				mish_check_unhandled(&mish),
				mish_check_syntax_error(&mish),
				mish_check_open_quotes(&mish));
		head = mish.error;
		while (mish.error)
		{
			printf("error : %d\n", mish.error->type);
			if (mish.error->data)
				printf("\tdata : %s\n", mish.error->data);
			mish.error = mish.error->next;
		}
		mish.error = head;
		if (mish_separate_processes(&mish))
		{
			if (!mish_fill_processes(&mish)) ///////////
				mish_print_processes(&mish);
			//print_process_lines(mish.p, mish.nb);

		}
		t_error_lst_free(&mish.error);
		free(mish.line);
	}
	return (0);
}
*/
