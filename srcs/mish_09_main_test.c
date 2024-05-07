/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_09_main_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:00 by bchene            #+#    #+#             */
/*   Updated: 2024/05/07 12:10:57 by bchene           ###   ########.fr       */
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
	char	*str[5]={"ls -a", "cat -e", "cat", "cat -e", NULL};

	mish_path_set(mish); 	// A METRE dans init p avant traitement de ligne
	mish->nb = ft_splitsize(str);
	mish_p_malloc(mish);
	i = -1;
	
	
	while (++i < mish->nb)
	{
		mish_p_init(mish, i, NULL);
		((mish->p) + i)->av = ft_split(str[i] , ' ');
		((mish->p) + i)->ac = ft_splitsize(((mish->p) + i)->av);
		t_process_cmd_get((mish->p) + i); // A METRE dans init p apres traitement de ligne
		// t_process_open_iofiles((mish->p) + i);
		// printf("iofd > %i, %i\n",t_process_get_iofd((mish->p) + i, 0), t_process_get_iofd((mish->p) + i, 1));
	}
	mish_fds_malloc(mish); // A METRE dans init p apres traitement de ligne
	mish_pid_malloc(mish); // A METRE dans init p apres traitement de ligne
	// mish_print(mish);
	mish_fork_parent(mish);
}

void	main_test_open_files(t_process *p)
{
	if (p->index == 0)
	{
		// t_process_add_file(p, "../test_minishell/corbeau444", tf_ifile_rdonly );
		// t_process_add_file(p, "../test_minishell/file2", tf_ofile_creat );
	}
	else if (p->index == 1)
	{
		//t_process_add_file(p, "../test_minishell/corbeau444", tf_ifile_rdonly );
		t_process_add_file(p, "../iofiles/file2", tf_ofile_creat );
	}
	else if (p->index == 2)
	{
		t_process_add_file(p, "../iofiles/corbeau.txt", tf_ifile_rdonly );
		// t_process_add_file(p, "../test_minishell/file2", tf_ofile_creat );
	}
	else if (p->index == 3)
	{
		// t_process_add_file(p, "../test_minishell/corbeau444", tf_ifile_rdonly );
		// t_process_add_file(p, "../test_minishell/file2", tf_ofile_creat );	
	}

	t_process_open_iofiles(p);

	printf("p%i <%i >%i\n", p->index, t_process_get_iofd(p, 0), t_process_get_iofd(p, 1));
	// << file2
	//t_process_add_file(mish->p + 0, "f2", tf_ifile_heredoc );
	// >> file4
	//t_process_add_file(mish->p + 0, "f4", tf_ofile_append );


}

int	t_process_heredoc(t_process *process)
{
	(void) process;
	return (-1);
}

void	t_process_open_infiles(t_process *p)
{
	t_file *tfile;

	tfile = p->infiles;
	while(tfile)
	{
		if (tfile->type == tf_ifile_rdonly) 
		{
			
			tfile->fd = open(tfile->path, O_RDONLY); // < 
			printf("open %s = %i\n", tfile->path, tfile->fd); //TEST
			if (tfile->fd == -1)
				mish_error_add(p->mish, err_fd_open, errno, tfile->path);
			else
				if (tfile->next)
					close_reset_fd(&(tfile->fd));
		}
		else if (tfile->type == tf_ifile_heredoc)
		{
			tfile->fd = t_process_heredoc(p); // << 
		}
		tfile = tfile->next;
	}
}

void	t_process_open_outfiles(t_process *p)
{
	t_file *tfile;

	tfile = p->outfiles;
	while(tfile)
	{		
		if (tfile->type == tf_ofile_creat)
		{
			tfile->fd = open(tfile->path, O_RDWR | O_CREAT | O_TRUNC, 0644); // > 
			if (tfile->fd == -1)
				mish_error_add(p->mish, err_fd_open, errno, tfile->path);
			else
				if (tfile->next)
					close_reset_fd(&(tfile->fd));
		}
		else if (tfile->type == tf_ofile_append)
		{
			tfile->fd = open(tfile->path, O_RDWR | O_CREAT | O_APPEND, 0644); // >>  
			if (tfile->fd == -1)
				mish_error_add(p->mish, err_fd_open, errno, tfile->path);
			else
				if (tfile->next)
					close_reset_fd(&(tfile->fd));
		}
		tfile = tfile->next;
	}
}

void	t_process_open_iofiles(t_process *process)
{
	t_process_open_infiles(process);
	t_process_open_outfiles(process);
}
