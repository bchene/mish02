/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish_12_pathlist.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/05/27 20:45:20 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"
/*
static t_err_type	mish_path_empty(t_mish *mish)
{
	mish->pathlist = malloc(sizeof(char *) * 2);
	if (mish->pathlist == NULL)
		return (mish_error_add(mish, err_malloc, errno, \
		"mish->pathlist == NULL"));
	mish->pathlist[0] = malloc(sizeof(char));
	if (mish->pathlist[0] == NULL)
		return (mish_error_add(mish, err_malloc, errno, \
		"mish->pathlist[0] == NULL"));
	mish->pathlist[0] = ft_strempty(mish->pathlist[0]);
	if (mish->pathlist[0] == NULL)
		return (mish_error_add(mish, err_malloc, errno, \
		"mish->pathlist[0] == NULL"));
	mish->pathlist[1] = NULL;
	return (0);
}
*/

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
	if(tmpstr)
		free(tmpstr);
	if(pwd)
		free(pwd);
	mish->pathlist = ft_split(pathstr, ':');
	// if (mish->pathlist == NULL)
	// {
	// 	mish_path_empty(mish);
	// 	free(pathstr);
	// 	return (0);
	// }
	i = -1;
	while (mish->pathlist[(++i)])
		mish->pathlist[i] = ft_strjointo(mish->pathlist[i], "/");
	//mish->pathlist[0] = ft_strempty(mish->pathlist[0]);
	free(pathstr);
	return (0);
}

/*
t_err_type	mish_path_set(t_mish *mish)
{
	int		i;
	char	*pathstr;
	char	*tmpstr;

	pathstr = ft_strdup(mish_env_get(mish, "PATH"));
	if (pathstr == NULL || ft_strlen(pathstr) == 0)
		return (mish_path_empty(mish));
	tmpstr = pathstr;
	pathstr = ft_strjoin(":", tmpstr);
	free(tmpstr);
	mish->pathlist = ft_split(pathstr, ':');
	if (mish->pathlist == NULL)
	{
		mish_path_empty(mish);
		free(pathstr);
		return (0);
	}
	i = 0;
	while (mish->pathlist[(++i)])
		mish->pathlist[i] = ft_strjointo(mish->pathlist[i], "/");
	mish->pathlist[0] = ft_strempty(mish->pathlist[0]);
	free(pathstr);
	return (0);
}
*/
