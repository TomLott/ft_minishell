/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 09:39:03 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/11 10:12:26 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_env(t_all *all, char *key)
{
	t_envlst	*tmp_env;
	char		cwd[4096];

	tmp_env = all->env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, key))
		{
			free(tmp_env->value);
			tmp_env->value = ft_strdup(getcwd(cwd, 4096));
		}
		tmp_env = tmp_env->next;
	}
}
