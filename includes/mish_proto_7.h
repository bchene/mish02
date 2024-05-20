/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_proto_7.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:11:01 by bchene            #+#    #+#             */
/*   Updated: 2024/05/20 18:46:42 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_PROTO_7_H
# define MISH_PROTO_7_H


/*						*/
/* 70_builtin			*/
void    t_process_builtin(t_process *process);
void    builtin_free(t_process *process);
void	builtin_error(t_process *p,char *str, int exitstatus);

/*						*/
/* 71_nocmd_pmish		*/
void	builtin_no_cmd(t_process *process);
void	builtin_no_access_cmd(t_process *process);
void	builtin_pmish(t_process *process);

/*						*/
/* 72_echo_cd_pwd		*/
void	builtin_echo(t_process *process);
void	builtin_cd(t_process *process);
void	builtin_pwd(t_process *process);

/*						*/
/* 73_export			*/
void	builtin_export(t_process *process);

/*						*/
/* 74_env_unset			*/
void	builtin_env(t_process *process);
void	builtin_unset(t_process *process);

#endif
