/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:31:47 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/07 10:11:15 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_env(char *env, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(env, '=');
	*eq = '\0';
	*key = ft_strdup(env);
	*value = ft_strdup(eq + 1);
}

t_envlst	*env_create(t_all *all, char *key, char *value)
{
	t_envlst	*ans;

	do_malloc(all, (void **)(&ans), ENV);
	ans->key = key;
	ans->value = value;
	ans->next = 0x0;
	return (ans);
}

int		check_head_env(t_all *all, t_list *tmp)
{
	t_envlst	*tmp_env;

	if (ft_strcmp(all->env->key, tmp->content))
	{
		tmp_env = all->env->next;
		free_env(&(all->env));
		all->env = tmp_env;
		return (1);
	}
	return (0);
}

void		env_add_back(t_all *all, char *env)
{
	char		*key;
	char		*value;
	t_envlst	*new_env;

	parse_env(env, &key, &value);
	new_env = env_create(all, key, value);
	if (!(all->env))
		all->env = new_env;
	else
	{
		new_env->next = all->env;
		all->env = new_env;
	}
}

void		ft_init_env(char **env, t_all *all)
{
	int	i;

	i = 0;
	while (env[i++])
		env_add_back(all, env[i - 1]);
}
