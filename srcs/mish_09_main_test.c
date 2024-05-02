/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_09_main_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:00 by bchene            #+#    #+#             */
/*   Updated: 2024/05/02 19:10:10 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

void	main_test_env(t_mish *mish)
{
	printf("LOGNAME=%s\n",mish_env_get(mish, "LOGNAME"));

	printf("NO_ENV=%s\n",mish_env_get(mish, "NO_ENV"));
	mish_env_add(mish, "NO_ENV", "SET_ENV");
	printf("NO_ENV=%s\n",mish_env_get(mish, "NO_ENV"));
	mish_env_remove(mish, "NO_ENV");
	printf("NO_ENV=%s\n",mish_env_get(mish, "NO_ENV"));
	/* tester ajout nom particulier */

	printf("0=%s\n",mish_unset_get(mish, "0"));
	printf("NO_UNUSET=%s\n",mish_unset_get(mish, "NO_UNUSET"));
	mish_unset_set(mish, "NO_UNUSET", "SET_UNUSET");
	printf("NO_UNUSET=%s\n",mish_unset_get(mish, "NO_UNUSET"));
	mish_unset_remove(mish, "NO_UNUSET");
	printf("NO_UNUSET=%s\n",mish_env_get(mish, "NO_UNUSET"));
	/* tester ajout nom particulier */

	mish_exit_status_set(mish, 124);
	printf("EXIT_STATUS=%i\n",mish_exit_status_get(mish));
}

void	main_test_set_process(t_mish *mish)
{
	int		i;
	char	*str[5]={"echo 1 2 3 4 5", "ls", "grep a", "cat -e", NULL};

	//ft_print_split(str);

	mish->nb = ft_splitsize(str);
	mish_p_malloc(mish);
	i = -1;
	while (++i < mish->nb)
	{
		mish_p_init(mish, i, NULL);
		((mish->p) + i)->av = ft_split(str[i] , ' ');
		((mish->p) + i)->ac = ft_splitsize(((mish->p) + i)->av);
	}
	mish_print(mish);

/*
	mish->nb = 3;
	mish_p_malloc(mish);
	if (mish_continue(mish))
	{
		mish_p_init(mish, 0, NULL);
		((mish->p) + 0)->av = ft_split("ls 1 2 3 4", ' ');
		((mish->p) + 0)->ac = ft_splitsize(((mish->p) + 0)->av);
		ft_printf_strtab( ((mish->p) + 0)->av , ((mish->p) + 0)->ac, "\\-\\");
		ft_print_split( ((mish->p) + 0)->av );
		//printf("%s\n", *(((mish->p) + 0)->av));

		mish_p_init(mish, 1, NULL);
		((mish->p) + 1)->av = ft_split("grep a", ' ');
		((mish->p) + 1)->ac = ft_splitsize(((mish->p) + 1)->av);

		mish_p_init(mish, 2, NULL);
		((mish->p) + 2)->av = ft_split("cat -e", ' ');
		((mish->p) + 2)->ac = ft_splitsize(((mish->p) + 2)->av);
	}
*/
}