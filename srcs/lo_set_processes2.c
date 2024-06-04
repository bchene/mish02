/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_set_processes2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:18:33 by locharve          #+#    #+#             */
/*   Updated: 2024/06/04 16:29:02 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_tfile_type	t_file_line_get_type(char *line)
{
	if (!ft_strncmp(line, "<<", 2))
		return (tf_ifile_heredoc);
	else if (!ft_strncmp(line, "<", 1))
		return (tf_ifile_rdonly);
	else if (!ft_strncmp(line, ">>", 2))
		return (tf_ofile_append);
	else if (!ft_strncmp(line, ">", 1))
		return (tf_ofile_creat);
	else
		return (tf_none);
}

char	*t_file_line_get_path(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] \
	&& (is_in_str(WHITESPACES, line[i]) \
	|| is_in_str("<>", line[i])))
		i++;
	return (&line[i]);
}
