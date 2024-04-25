/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_parsing_prototypes.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:26:06 by locharve          #+#    #+#             */
/*   Updated: 2024/04/25 19:53:07 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_PARSING_PROTOTYPES
# define MISH_PARSING_PROTOTYPES

# include "mish.h"

/*	ft_isalpha
	ft_strdup
	ft_strndup
	ft_strcpy
	ft_strlen
	ft_memmove
	ft_strncmp
	ft_strchr
	ft_calloc
	ft_bzero
	ft_itoa
	ft_split
	ft_splitsize
	is_alphanum_underscore ///// ok
	ft_strlen_while ///// ok
	is_in_str // ok
	strtab_free /////
/*
/* mish_parsing.c */
int		mish_parsing(t_mish *mish);

/* mish_substitute_vars.c */
int		is_there_a_var(char *str);
char	*get_var_value(t_mish *mish, char *var);
char	*substitute_hub(t_mish *mish, char *src, char *var);
void	mish_var_dup(t_mish *mish, char **line, char *var);
void	mish_substitute_vars(t_mish *mish, char **p_lines);
void	mish_remove_quotes(t_mish *mish, char **p_lines);

/* substitute_fonctions.c */
char	*get_var_value(t_mish *mish, char *var);
char	*dup_substituting(t_mish *mish, char *src, char *var, char *sub);
char	*substitute_exit_status(t_mish *mish, char *src, char *var);
char	*substitute_digits(t_mish *mish, char *src, char *var);
char	*substitute_var(t_mish *mish, char *src, char *var);

/* mish_04_t_error.c */
void	t_error_add(t_error **lst, t_error *new);
t_error	*t_error_new(t_err_type t, int en, char *d);
t_err_type	mish_t_error_add(t_mish *mish, t_err_type t, int en, char *d);

/* mish_check_syntax_error.c */
// int	is_special_token(char *line, int i);
// char	*next_char_addr(char *str);
// int	dup_err_str(t_mish *mish, char *src, int n, t_err_type err);
int		mish_check_syntax_error(t_mish *mish);
int		mish_check_open_quotes(t_mish *mish);

/* mish_check_unhandled.c */
int		is_between_quotes(t_mish *mish, char *line, int i);
int		mish_check_unhandled(t_mish *mish);

/* mish_separate_processes.c */
int		char_count(char *str, char c);
void	process_init_line(t_process **p, char **split, int count);
void	mish_init_p_mish(t_mish *mish);
int		mish_separate_processes(t_mish *mish);

/* mish_fill_processes.c */
void	file_add_back(t_file **lst, t_file *new);
// char	**strtab_get_io_files(char **split);
// void	process_fill_io_files(t_process *p, char **split);
// void	process_fill_av(t_process *p, char **split);
// int	process_fill(t_mish *mish, t_process *p);
int		mish_fill_processes(t_mish *mish);

/* mish_split.c */
int			count_words(char *str, char *sep);
// char		*substr_dup(char *str, int start, int end);
// char		*from_str_to_strs(char *str, int *i, char *sep);
char		**mish_split(t_process *p, char *sep);

/* handle_word.c */
int			handle_quotes(char *str, int i, char q);
int			handle_redirections(char *str, int i, char r);
int			handle_specials(char *str, int i);
int			handle_word(char *str, char *sep, int i);

/////////////////////////////////////////////////////////////////////

/* is_in_str.c */
int			is_digit(char c);
int			is_in_str(char *str, char c);

/* mish_91_ft_01.c */
int			is_alphanum_underscore(char c);
size_t		ft_strlen_while(char *str, int )

#endif