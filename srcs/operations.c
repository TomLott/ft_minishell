/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:51:38 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/09 12:38:40 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env(t_all *all)
{
	t_envlst	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (tmp->key)
			ft_putstr_fd(tmp->key, STDIN_FILENO);
		ft_putstr_fd("=", STDIN_FILENO);
		ft_putstr_fd(tmp->value, STDIN_FILENO);
		ft_putstr_fd("\n", STDIN_FILENO);
		tmp = tmp->next;
	}
	return (0);
}

int	ms_pwd(void)
{
	char	cwd[4096];

	if (!(getcwd(cwd, 4096)))
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (-1);
	}
	else
	{
		ft_putstr_fd(cwd, STDIN_FILENO);
		ft_putstr_fd("\n", STDIN_FILENO);
	}
	return (0);
}

int	ms_unset(t_all *all)
{
	t_list		*tmp;
	t_envlst	*tmp_env;
	t_envlst	*prev;

	tmp = all->args.args;
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
	return (0);
}

int	ms_def(t_all *all)
{
	if (*(all->line) == 0)
		return (0);

	ft_putstr_fd(all->line, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (-1);
}

int	ms_export(t_all *all)
{
	t_list	*args;
	char	*tmp;

	args = all->args.args;
	while (args)
	{
		if ((tmp = convert_env(args->content)))
			env_add_back(all, tmp);
		args = args->next;
	}
	return (0);
}
