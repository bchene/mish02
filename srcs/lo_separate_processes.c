/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_separate_processes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:12:20 by bchene            #+#    #+#             */
/*   Updated: 2024/04/25 17:12:23 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mish.h"

void	process_init_line(t_process **p, char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		(*p + i)->line = split[i];
		i++;
	}
	return ;
}

void	mish_init_p_mish(t_mish *mish)
{
	int	i;

	i = 0;
	while (i < mish->nb)
	{
		mish->p[i].mish = mish;
		i++;
	}
	return ;
}

/**/
/* a adapter avec t_process */
/**/

int	mish_separate_processes(t_mish *mish)
{
	char	**p_lines;
	int		count;
	
	p_lines = NULL;
//	if (!mish_check_syntax_error(mish) && !mish_check_unhandled(mish)
//			&& !mish_check_open_quotes(mish))
//	{
		count = char_count(mish->line, '|') + 1;
		mish->p = ft_calloc(count, sizeof(*(mish->p))); // malloc
		if (mish->p)
		{
			p_lines = ft_split(mish->line, '|'); // malloc
			if (p_lines)
			{
				mish->nb = count;
				process_init_line(&mish->p, p_lines, count);
				mish_init_p_mish(mish);
				free(p_lines);
			}
		}
		else
			return (0);
//	}
	return (1);
}
