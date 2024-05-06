/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_09_main_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:00 by bchene            #+#    #+#             */
/*   Updated: 2024/05/06 15:53:02 by bchene           ###   ########.fr       */
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
	char	*str[5]={"marche pas", "ls -a", "cat -e", "cat", NULL};

	mish_path_set(mish); // a mettre dans init p avant traitement de ligne
	mish->nb = ft_splitsize(str);
	mish_p_malloc(mish);
	i = -1;
	while (++i < mish->nb)
	{
		mish_p_init(mish, i, NULL);
		((mish->p) + i)->av = ft_split(str[i] , ' ');
		((mish->p) + i)->ac = ft_splitsize(((mish->p) + i)->av);
		t_process_cmd_get((mish->p) + i); // a mettre dans init p apres traitement de ligne
	}
	mish_fds_malloc(mish); // a mettre dans init p apres traitement de ligne
	mish_pid_malloc(mish); // a mettre dans init p apres traitement de ligne
	//mish_print(mish);
	mish_fork_parent(mish);
	//ft_freesplit(str);
	//printf("FIN");
}