/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 09:39:03 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/11 15:14:05 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(t_all *all)
{
	t_envlst	*tmp_env;
	char		cwd[4096];

	tmp_env = all->env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, "PWD"))
		{
			free(tmp_env->value);
			tmp_env->value = ft_strdup(getcwd(cwd, 4096));
		}
		tmp_env = tmp_env->next;
	}
}

void	set_old_pwd(t_all *all)
{
	t_envlst	*tmp_env;

	tmp_env = all->env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, "OLDPWD"))
		{
			free(tmp_env->value);
			tmp_env->value = extract_env(all->env, "PWD");
		}
		tmp_env = tmp_env->next;
	}
}
