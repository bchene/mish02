/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_proto_0.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:11:01 by bchene            #+#    #+#             */
/*   Updated: 2024/04/26 20:15:08 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_PROTO_0_H
# define MISH_PROTO_0_H

/*						*/
/* 01-00 mish 			*/
t_err_type	mish_init(t_mish *mish, char **envp);
t_err_type	mish_init_bis(t_mish *mish, char **envp);
void		mish_free(t_mish *mish);
void		mish_reset(t_mish *mish);
void		mish_print(t_mish *mish);

/* 01-01 mish->error */
t_err_type	mish_t_error_add(t_mish *mish, t_err_type t, int en, char *d);

/* 01-02 mish->prompt */

/* 01-03 mish->line */

/* 01-04 mish->splitline */

/* 01-05 mish->p */
t_err_type	mish_p_malloc(t_mish *mish);
void		mish_p_free(t_mish *mish);
t_err_type	mish_p_init(t_mish *mish, int index, char *line);
void		mish_p_print(t_mish *mish);

/* 01-06 mish->fds */
t_err_type	mish_fds_malloc(t_mish *mish);
void		mish_fds_close(t_mish *mish);
void		mish_fds_free(t_mish *mish);
void		mish_fds_print(t_mish *mish);

/* 01-07 mish->pid */
void		mish_pid_print(t_mish *mish);

/* 01-08 mish->env */
char		*mish_env_get(t_mish *mish, char *var);
int			mish_env_set(t_mish *mish, char *var, char *value);
int			mish_env_add(t_mish *mish, char *var, char *value);

/* 01-09 mish->unset */
char		*mish_unset_get(t_mish *mish, char *var);
int			mish_unset_set(t_mish *mish, char *var, char *value);

/* 01-10 mish->env_unset */
void		mish_env_unset_init(t_mish *mish, char **envp);
void		mish_env_unset_free(t_mish *mish);
void		mish_env_unset_print(t_mish *mish);

/* 01-11 exit status */
void		mish_exit_status_set(t_mish *mish, char *value);
char		*mish_exit_status_get(t_mish *mish);

/* 01-12 mish->path */
t_err_type	mish_path_set(t_mish *mish);

/*						*/
/* 02_t_error			*/
t_error		*t_error_new(t_err_type t, int en, char *d);
void		t_error_add(t_error **lst, t_error *new);
void		t_error_del(t_error *err);
void		t_error_lst_free(t_error **err);
t_err_type	t_error_exist(t_error *err);
void		t_error_print(t_error *err);

/*						*/
/* 03_t_env 			*/
t_env		*t_env_new(char *str);
t_env		*t_env_add(t_env **env, char *str);
void		t_env_del(t_env *env);
void		t_env_free(t_env *env);
int			t_env_remove(t_env **env, t_env *to_remove);
t_env		*t_env_getvar(t_env *env, char *var);
char		*t_env_getdata(t_env *env, char *var);
int			t_env_setstr(t_env *env, char *var, char *value);
void		t_env_print(t_env *tenv);

#endif
