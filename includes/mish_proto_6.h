/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_proto_6.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:11:01 by bchene            #+#    #+#             */
/*   Updated: 2024/05/21 16:44:39 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_PROTO_6_H
# define MISH_PROTO_6_H

/*						*/
/* 60_t_file    		*/
t_file	*t_file_new(t_mish *mish, char *path, t_tfile_type type);
void	t_file_free(t_file **tf);
void	t_file_del(t_file **tf);
void	t_process_iofiles_error(t_process *p, int en, char *path, int *err);

/*						*/
/* 61_p_files_open		*/
// void	t_process_open_infiles(t_process *p, t_tfile_type type);
// void	t_process_open_outfiles(t_process *p);
void	mish_open_iofiles(t_mish *mish);
void	t_process_open_heredoc(t_process *p, int openfile);
void	t_process_open_iofiles(t_process *p, int *err);

/*						*/
/* 62_p_files_close		*/
void	t_process_close_iofile(t_process *p);
void	mish_p_iofiles_close(t_mish *mish);
void	mish_heredocs_unlink(t_mish *mish);

/*						*/
/* 63_p_files_heredoc		*/
void	t_file_heredoc(t_file *tfile, int openfile, t_mish *mish);

#endif
