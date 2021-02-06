/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:51:38 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/06 21:58:49 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(t_all *all)
{
	t_envlst	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (tmp->key)
			ft_putstr_fd(tmp->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(tmp->value, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

void	ms_pwd(void)
{
	char	cwd[4096];

	if (!(getcwd(cwd, 4096)))
		ft_putstr_fd("Error while getting working directory\n", 1);
	else
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}

}

void	ms_unset(t_all *all)
{
	t_list		*tmp;
	t_envlst	*tmp_env;
	t_envlst	*prev;

	tmp = all->args;
	while (tmp)
	{
		if (check_head_env(all, tmp))
			continue ;
		tmp_env = all->env->next;
		prev = all->env;
		while (tmp_env)
		{
			if (ft_strcmp(tmp->content, tmp_env->key))
			{
				prev->next = tmp_env->next;
				free_env(&tmp_env);
			}
			prev = tmp_env;
			tmp_env = tmp_env->next;
		}
		tmp = tmp->next;
	}
}
