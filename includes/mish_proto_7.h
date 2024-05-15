/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_proto_7.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:11:01 by bchene            #+#    #+#             */
/*   Updated: 2024/05/15 17:47:17 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_PROTO_7_H
# define MISH_PROTO_7_H

void	    t_process_builtin(t_process *process);
void	    builtin_free(t_process *process);
t_err_type	builtin_no_access(t_process *process);

#endif
