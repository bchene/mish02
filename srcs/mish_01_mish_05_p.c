/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_05_p.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/09 16:35:11 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_err_type	mish_p_malloc(t_mish *mish)
{
	// gerer erreur vide
	if (mish == NULL && mish->nb < 1)
		return (-1);
	mish->p = ft_calloc(mish->nb, sizeof(t_process));
	if (mish->p == NULL)
	{
		mish_error_add(mish, err_malloc, errno, "mish->p == NULL");
		return (t_error_exist(mish->error));
	}
	return (0);
}

void	mish_p_free(t_mish *mish)
{
	int	i;

	if (mish && mish->p)
	{
		i = -1;
		while(++i < mish->nb)
			t_process_free((mish->p) + i);
		free(mish->p);
	}
}

t_err_type	mish_p_init(t_mish *mish, int index, char *line)
{
	t_process	*process;

	process = (mish->p) + index;
	if (process == NULL)
	{
		mish_error_add(mish, err_other, errno, "t_process_new == NULL");
		return (t_error_exist(mish->error));
	}
	process->mish = mish;
	process->index = index;
	process->line = line;
	process->ac = 0;
	process->av = NULL;
	process->cmd = NULL;
	process->infiles = NULL;
	process->outfiles = NULL;
	return (0);
}

t_err_type	mish_p_parse(t_mish *mish)
{
	int	i;

	i = -1;
	while (++i < mish->nb)
	{
		if (mish_p_init(mish, i, mish->splitline[i]))
			return (t_error_exist(mish->error));
		// pas de gestion d erreur? rempli iofiles ac et av
		t_process_set((mish->p) + i);
		// main_test_open_files((mish->p) + i); //TEST
		t_process_cmd_get((mish->p) + i); // A METRE dans init p apres traitement de ligne
		t_process_open_iofiles((mish->p) + i);
	}
	// METTRE DANS mish_exec
	// if (mish_fork_parent(mish))
	// 	return (t_error_exist(mish->error));
	return (0);
}

void	mish_p_print(t_mish *mish)
{
	int	i;

	if (mish && mish->nb > 0 && mish->p)
	{
		i = -1;
		while(++i < mish->nb)
			t_process_print((mish->p) + i);
	}
	else
		printf("(null)\n");
}
