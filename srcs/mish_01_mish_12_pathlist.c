/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_12_pathlist.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/31 13:23:03 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_err_type	mish_path_set(t_mish *mish)
{
	int		i;
	char	*pathstr;
	char	*tmpstr;
	char	*pwd;

	tmpstr = ft_strdup(mish_env_get(mish, "PATH"));
	pwd = malloc(1024 * sizeof(char));
	getcwd(pwd, 1024);
	if (tmpstr == NULL || ft_strlen(tmpstr) == 0)
		pathstr = ft_strjoinva(pwd, NULL);
	else
		pathstr = ft_strjoinva(pwd, ":", tmpstr, NULL);
	if (tmpstr)
		free(tmpstr);
	if (pwd)
		free(pwd);
	mish->pathlist = ft_split(pathstr, ':');
	i = -1;
	while (mish->pathlist[(++i)])
		mish->pathlist[i] = ft_strjointo(mish->pathlist[i], "/");
	free(pathstr);
	return (0);
}
