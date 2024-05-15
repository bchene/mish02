/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_63_p_files_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:36:25 by bchene            #+#    #+#             */
/*   Updated: 2024/05/15 18:22:08 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

int	t_file_heredoc(t_file *file)
{
	char	*line;

	line = readline(">");
	return (file->fd);  //TMP
	/*
	while(line || !line[0] || strncmp(line, file->path, ))
	{
		line = readline(">");
	}
	*/
}

int	t_process_heredoc(t_process *process)
{
	(void) process;
	return (-1);
	//boucle creation de tous les HD d un process
}
