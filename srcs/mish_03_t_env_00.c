/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_03_t_env_00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchene <bchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:07:17 by bchene            #+#    #+#             */
/*   Updated: 2024/05/15 18:25:15 by bchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish.h"

t_env	*t_env_new(char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}

t_env	*t_env_add(t_env **env, char *str)
{
	t_env	*new;
	t_env	*cur;

	new = t_env_new(str);
	if (new == NULL)
		return (NULL);
	if (*env == NULL)
	{
		*env = new;
		return (new);
	}
	cur = *env;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (new);
}

void	t_env_del(t_env **env)
{
	if (*env)
	{
		if ((*env)->str)
		{
			free ((*env)->str);
		}	
		free (*env);
		*env = NULL; // A TESTER
	}
}

void	t_env_free(t_env **env)
{
	if (*env)
	{
		if ((*env)->next)
			t_env_free(&((*env)->next));
		t_env_del(env);
	}
}

int	t_env_remove(t_env **env, t_env *to_remove)
{
	t_env	*cur;

	if (env == NULL || to_remove == NULL)
		return (-1);
	cur = *env;
	if (cur == to_remove)
	{
		*env = cur->next;
		t_env_del(&to_remove);
		return (0);
	}
	while (cur->next && (cur->next != to_remove))
		cur = cur->next;
	if (cur->next == to_remove)
	{
		cur->next = to_remove->next;
		t_env_del(&to_remove);
		return (0);
	}
	return (1);
}
