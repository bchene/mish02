/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_proto_5.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:11:01 by bchene            #+#    #+#             */
/*   Updated: 2024/05/09 16:06:51 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_PROTO_5_H
# define MISH_PROTO_5_H

/*						*/
/* 50_process			*/
void		t_process_free(t_process *process);
char		*t_process_cmd_get(t_process *process);
//void		t_process_t_file_set(t_process *process);
//void		t_process_arg_set(t_process *process);
void		t_process_print(t_process *p);

/*						*/
/* 51_process_iofiles	*/
t_file		*t_process_iofile_add(t_process *p, char *path, t_tfile_type type);
int			t_process_iofile_get(t_process *process, int inorout);
void        t_process_iofile_print(t_process *process);
t_file		*t_process_line_to_file(t_process *p, char *line);
void		t_file_add_back_rec(t_file **lst, t_file *new);
t_file      *t_process_add_file(t_process *p, char *path, t_tfile_type type);

/*						*/
/* 52_process_pipe		*/
void		close_reset_fd(int *fd);
t_err_type	t_process_pipe_fds(t_process *process);
t_err_type	t_process_dup_io(t_process *p);

/*						*/
/* 53_process_exec		*/
t_err_type	mish_start_process(t_mish *mish);
t_err_type	mish_fork_parent(t_mish *mish);
t_err_type	t_process_fork_child(t_process *p);

#endif
