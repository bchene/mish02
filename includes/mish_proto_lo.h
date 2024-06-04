/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_proto_lo.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:11:01 by bchene            #+#    #+#             */
/*   Updated: 2024/06/04 16:41:33 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_PROTO_LO_H
# define MISH_PROTO_LO_H

/* check_syntaxe_error */
char			*token_dup(char *str);
int				mish_check_syntax_error(t_mish *mish);
int				is_first_tkn(char *line, char *tkn_addr);
void			mish_set_unexpected_error(t_mish *mish, char *curr_t, \
char *next_t);

/* check_open_quotes */
int				mish_check_open_quotes(t_mish *mish);

/* check_unhandled */
int				is_between_quotes(char *str, int i);
int				mish_check_unhandled(t_mish *mish);

/* fill_processes */
void			file_add_back(t_file **lst, t_file *new);

/* handle word */
int				handle_quotes(char *str, int i, char q);
int				handle_redirections(char *str, int i, char r);
int				handle_specials(char *str, int i);
int				handle_word(char *str, char *sep, int i);

/* parsing */
int				mish_parsing(t_mish *mish);

/* mish_split */
char			**mish_split(char *s, char c);

/* t_process_split */
int				count_words(char *str, char *sep);
char			**t_process_split(t_process *p, char *sep);

/* substitute vars */
int				is_there_a_var(char *str);
char			*get_var_value(t_mish *mish, char *var);
char			*substitute_hub(t_mish *mish, char *src, char *var);
void			mish_var_dup(t_mish *mish, char **line, char *var);
void			mish_substitute_vars(t_mish *mish, char **p_lines);

/* mish_remove_quotes */
t_err_type		mish_remove_quotes(t_mish *mish, char **p_lines);

/* substitute vars */
char			*copy_sub(char *dst, char *src, char *var, char *sub);
char			*dup_substituting(char *src, char *var, char *sub);
char			*substitute_0(t_mish *mish, char *src, char *var);
char			*substitute_exit_status(t_mish *mish, char *src, char *var);
char			*substitute_var(t_mish *mish, char *src, char *var);

/* lo_substitute_2 */
char			*mish_substitute_str(t_mish *mish, int f(char *, int), \
char *str);
char			**mish_substitute_strtab(t_mish *mish, int f(char *, int), \
char **strtab);

/* lo_set_processes */
void			t_process_set(t_process *p);
void			t_process_iofiles_args_set(t_process *p, char **iofiles, \
char **args);
void			t_process_t_file_set(t_process *p, char **strtab);
void			t_process_args_set(t_process *p, char **strtab);
char			*t_file_line_get_path(char *line);
t_tfile_type	t_file_line_get_type(char *line);

/* lo_strtab_if */
char			**strtab_dup_if(char **src, t_tfile_type f(char *), int b);

/* ft_strjoin_tab */
size_t			ft_strlen_tab(char **strtab);
char			*ft_strcpy_tab(char *dst, char **srcs, char sep);
char			*ft_strjoin_tab(char **strtab, char sep);

/* lo_mish_parse_line.c */
t_err_type		mish_first_substitution(t_mish *mish);
t_err_type		mish_check_line(t_mish *mish);

/* lo_strtab.c */
char			**strtab_addstr(char **strtab, char *str);
void			strtab_print(char **strtab, char *sep);

/* lo_signals.c */
void			handler_set_type(t_handeler_type type);

#endif
