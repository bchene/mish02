/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_proto_lo.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:11:01 by bchene            #+#    #+#             */
/*   Updated: 2024/04/25 19:52:08 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_PROTO_LO_H
# define MISH_PROTO_LO_H

/* check_syntaxe_error */
int		mish_check_syntax_error(t_mish *mish);
int		mish_check_open_quotes(t_mish *mish);

/* check_unhandled */
int		is_between_quotes(t_mish *mish, char *line, int i);
int		mish_check_unhandled(t_mish *mish);

/* fill_processes */
void	file_add_back(t_file **lst, t_file *new);
int		mish_fill_processes(t_mish *mish);

/* handle word */
int		handle_quotes(char *str, int i, char q);
int		handle_redirections(char *str, int i, char r);
int		handle_specials(char *str, int i);
int		handle_word(char *str, char *sep, int i);

/* parsing */
int		mish_parsing(t_mish *mish);

/* print_free */
void	print_process_lines_free(t_process *p, int count);
void	print_files_free(t_file *lst);
void	print_split_free(char **split);
void	mish_print_processes_free(t_mish *mish);

/* separate processes */
void	process_init_line(t_process **p, char **split, int count);
void	mish_init_p_mish(t_mish *mish);
int		mish_separate_processes(t_mish *mish);

/* split mish */
int		count_words(char *str, char *sep);
char	**mish_split(t_process *p, char *sep);

/* substitute vars */
int		is_there_a_var(char *str);
char	*get_var_value(t_mish *mish, char *var);
char	*substitute_hub(t_mish *mish, char *src, char *var);
void	mish_var_dup(t_mish *mish, char **line, char *var);
void	mish_substitute_vars(t_mish *mish, char **p_lines);
void	mish_remove_quotes(t_mish *mish, char **p_lines);

/* substitute vars */
char	*copy_sub(char *dst, char *src, char *var, char *sub);
char	*dup_substituting(char *src, char *var, char *sub);
char	*substitute_0(t_mish *mish, char *src, char *var);
char	*substitute_exit_status(t_mish *mish, char *src, char *var);
char	*substitute_var(t_mish *mish, char *src, char *var);

#endif
