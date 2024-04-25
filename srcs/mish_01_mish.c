/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_01_mish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:08 by bchene            #+#    #+#             */
/*   Updated: 2024/04/25 21:46:35 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_err_type	mish_init(t_mish *mish, char **env)
{
	ft_bzero(mish, sizeof(t_mish));
	mish_env_init(mish, env);
	return (t_error_exist(mish->error));
}

t_err_type	mish_init_bis(t_mish *mish, char **env)
{
	mish->error->type = 0;
	mish->error->data = NULL;
	mish->prompt = NULL;
	mish->line = NULL;
	mish->splitline = NULL;
	mish->nb = 0;
	mish->p = NULL;
	mish->fds = NULL;
	mish->pid = NULL;
	mish_env_init(mish, env);
	mish->pathlist = NULL;
	return (t_error_exist(mish->error));
}

void	mish_free(t_mish *mish)
{
	if (mish->error->data)
		free(mish->error->data);
	if (mish->prompt)
		free(mish->prompt);
	if (mish->line)
		free(mish->line);
	if (mish->splitline)
		ft_freesplit(mish->splitline);
	if (mish->p)
		mish_p_free(mish);
	if (mish->fds)
		free(mish->fds);
	if (mish->pid)
		free(mish->pid);
	mish_envunset_free(mish);
	ft_freesplit(mish->pathlist);
}

void	mish_reset(t_mish *mish)
{
	if (mish->error->data)
		free(mish->error->data);
	mish->error->type = 0;
	if (mish->line)
		free(mish->line);
	if (mish->splitline)
		ft_freesplit(mish->splitline);
	mish->nb = 0;
	if (mish->p)
		mish_p_free(mish);
	if (mish->fds)
		free(mish->fds);
	if (mish->pid)
		free(mish->pid);
	//ft_freesplit(mish->pathlist);
}

static t_err_type	mish_path_empty(t_mish *mish)
{
	mish->pathlist = malloc(sizeof(char *) * 2);
	if (mish->pathlist == NULL)
		return (mish_t_error_add(mish, err_malloc, errno, 
		"mish->pathlist == NULL"));	
	mish->pathlist[0] = malloc(sizeof(char));
	if (mish->pathlist[0] == NULL)
		return (mish_t_error_add(mish, err_malloc, errno, 
		"mish->pathlist[0] == NULL"));		
	mish->pathlist[0] = ft_strempty(mish->pathlist[0]);
	if (mish->pathlist[0] == NULL)
		return (mish_t_error_add(mish, err_malloc, errno, 
		"mish->pathlist[0] == NULL"));
	mish->pathlist[1] = NULL;
	return (0);
}

t_err_type	mish_path_set(t_mish *mish)
{
	int		i;
	char	*pathstr;
	char	*tmpstr;

	pathstr = ft_strdup(mish_env_get(mish,"PATH"));
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
		return (mish->error->type);
	}
	i = 0;
	while (mish->pathlist[(++i)])
		mish->pathlist[i] = ft_strjointo(mish->pathlist[i], "/");
	mish->pathlist[0] = ft_strempty(mish->pathlist[0]);
	free(pathstr);
	return (err_none);
}

// si erreur de malloc dans erreur comment sortir
t_err_type	mish_t_error_add(t_mish *mish, t_err_type t, int en, char *d)
{
	t_error	*new;

	new = t_error_new(t, en, d);
	if (new)
		t_error_add(&(mish->error), new);
	else
		return (err_malloc);
	return (t);
}

char	*mish_env_get(t_mish *mish, char *var)
{
	char *str;

	str = t_env_getdata(mish->env, var);
	return (str);
}

int	mish_env_set(t_mish *mish, char *var, char *value)
{
	int ret;

	if (t_env_getvar(mish->env, var))
		ret = t_env_setstr(mish->env, var, value);
	else
		ret = -1;
	return (ret);
}

int	mish_env_add(t_mish *mish, char *var, char *value)
{
	int ret;
	
	ret = t_env_setstr(mish->env, var, value);
	return (ret);
}

char	*mish_unset_get(t_mish *mish, char *var)
{
	char *str;

	str = t_env_getdata(mish->unset, var);
	return (str);
}

int	mish_unset_set(t_mish *mish, char *var, char *value)
{
	int ret;

	ret = t_env_setstr(mish->unset, var, value);
	return (ret);
}

void	mish_exit_status_set(t_mish *mish, char *value)
{
	mish_unset_set(mish, "?", value);
}

char	*mish_exit_status_get(t_mish *mish)
{
	char *exit_status;

	exit_status = mish_unset_get(mish, "?");
	return (exit_status);
}

void	mish_env_init(t_mish *mish, char **env)
{
	while (*env)
	{
		t_env_add(&(mish->env), *env);
		(*env)++;
	}
	t_env_add(&(mish->unset), "?=0");
	t_env_add(&(mish->unset), "0=minishell");
}

void	mish_envunset_free(t_mish *mish)
{
	t_env_free(mish->env);
	t_env_free(mish->unset);
}

t_err_type	mish_p_malloc(t_mish *mish)
{
	// gerer erreur vide
	if (mish == NULL && mish->nb < 1)
		return (t_error_exist(mish->error));
	mish->p = ft_calloc(mish->nb, sizeof(t_process));
	if (mish->p == NULL)
		mish_t_error_add(mish, err_malloc, errno, "mish->p == NULL");
	return (t_error_exist(mish->error));
}

void	mish_p_free(t_mish *mish)
{
	int	i;

	if (mish && mish->nb > 0 && mish->p)
	{
		i = -1;
		while(++i < mish->nb)
			t_process_free((mish->p) + i);
		free(mish->p);
	}
}

t_err_type	mish_p_init(t_mish *mish, int index, char *line)
{
	t_process	*process;

	process = (mish->p) + index;
	if (process == NULL)
	{
		mish_t_error_add(mish, err_other, errno, "t_process_new == NULL");
		return (t_error_exist(mish->error));
	}
	process->mish = mish;
	process->index = index;
	process->line = line;
	process->ac = 0;
	process->av = NULL;
	process->cmd = NULL;
	process->infiles = NULL;
	process->outfiles = NULL;
	return (t_error_exist(mish->error));
}

t_err_type	mish_fds_malloc(t_mish *mish)
{
	int	i;

	mish->fds = malloc((mish->nb + 1) * sizeof(int *));
	if (mish->fds == NULL)
		return (mish_t_error_add(mish, err_malloc, errno, "mish->fds == NULL"));
	i = -1;
	while (++i < mish->nb + 1)
	{
		(mish->fds)[i] = malloc(2 * sizeof(int));
		if ((mish->fds)[i] == NULL)
			return (mish_t_error_add(mish, err_malloc, errno, "(mish->fds)[i] == NULL"));
		(mish->fds)[i][0] = -1;
		(mish->fds)[i][1] = -1;
	}
	return (mish->error->type);
}

void	mish_fds_close(t_mish *mish)
{
	int	i;

	i = -1;
	while (++i < (mish->nb + 1))
	{
		close_reset_fd(((mish->fds)[i]));
		close_reset_fd((mish->fds[i] + 1));
	}
}

void	mish_fds_free(t_mish *mish)
{
	int	i;

	i = -1;
	while (++i < mish->nb + 1)
		if (mish && mish->fds && (mish->fds)[i])
			free((mish->fds)[i]);
	if (mish && mish->fds )
		free(mish->fds);
}

void	mish_print(t_mish mish)
{
	(void) mish;
}