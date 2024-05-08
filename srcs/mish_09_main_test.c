/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_09_main_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:00 by bchene            #+#    #+#             */
/*   Updated: 2024/05/08 17:54:21 by bchene           ###   ########.fr       */
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
	char	*str[5]={"ls", "cat", "cat", "cat", NULL};

	mish_path_set(mish); 	// A METRE dans init p avant traitement de ligne
	mish->nb = ft_splitsize(str);
	mish_p_malloc(mish);
	mish_fds_malloc(mish); // A METRE dans init p apres traitement de ligne
	mish_pid_malloc(mish); // A METRE dans init p apres traitement de ligne	
	i = -1;
	while (++i < mish->nb)
	{
		mish_p_init(mish, i, NULL);
		((mish->p) + i)->av = ft_split(str[i] , ' ');
		((mish->p) + i)->ac = ft_splitsize(((mish->p) + i)->av);
		t_process_cmd_get((mish->p) + i); // A METRE dans init p apres traitement de ligne
		main_test_open_files((mish->p) + i);
		// t_process_open_iofiles((mish->p) + i);
		// printf("iofd > %i, %i\n",t_process_iofile_get((mish->p) + i, 0), t_process_iofile_get((mish->p) + i, 1));
	}

	//main_test_open_files(process); // TESTE
	// OPEN FILES << les open se font avant les forks	
	// mish_print(mish);
	mish_fork_parent(mish);
}

void	main_test_open_files(t_process *p)
{
	if (p->index == 0)
	{
		t_process_iofile_add(p, "../iofiles/corbeau.txt", tf_ifile_rdonly );
		// t_process_iofile_add(p, "../iofiles/tf0", tf_ofile_creat );
	}
	else if (p->index == 1)
	{
		// t_process_iofile_add(p, "../iofiles/corbeau.txt", tf_ifile_rdonly );
		// t_process_iofile_add(p, "../iofiles/tf1", tf_ofile_creat );
	}
	else if (p->index == 2)
	{
		//t_process_iofile_add(p, "../iofiles/corbeau.txt", tf_ifile_rdonly );
		// t_process_iofile_add(p, "../iofiles/tf2", tf_ofile_creat );
	}
	else if (p->index == 3)
	{
		// t_process_iofile_add(p, "../iofiles/corbeau444", tf_ifile_rdonly );
		// t_process_iofile_add(p, "../iofiles/tf3", tf_ofile_creat );	
	}

	t_process_open_iofiles(p);

	//printf("p%i <%i >%i\n", p->index, t_process_iofile_get(p, 0), t_process_iofile_get(p, 1));
	
	// << file2
	//t_process_iofile_add(mish->p + 0, "f2", tf_ifile_heredoc );
	// >> file4
	//t_process_iofile_add(mish->p + 0, "f4", tf_ofile_append );


}

