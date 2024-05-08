/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_proto_6.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:11:01 by bchene            #+#    #+#             */
/*   Updated: 2024/05/08 17:54:27 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_PROTO_6_H
# define MISH_PROTO_6_H

/*						*/
/* 60_t_file    		*/
t_file	*t_file_new(t_mish *mish, char *path, t_tfile_type type);
void	t_file_free(t_file *tf);
void	t_file_del(t_file *tf);

/*						*/
/* 61_p_files_open		*/
void	t_process_open_iofiles(t_process *process);
void	t_process_open_infiles(t_process *p);
void	t_process_open_outfiles(t_process *p);
/*						*/
/* 62_p_files_close		*/
void	t_process_close_infile(t_process *p);
void	t_process_close_outfile(t_process *p);
void	mish_p_iofiles_close(t_mish *mish);
/*						*/
/* 63_p_files_heredoc		*/
int		t_process_heredoc(t_process *process);

#endif
