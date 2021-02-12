/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:51:38 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/12 19:37:19 by jmogo            ###   ########.fr       */
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
	char		**tmp;
	t_envlst	*tmp_env;
	t_envlst	*prev;

	tmp = all->args.args;
	while (tmp)
	{
		//if (check_head_env(all, tmp))
		//	continue ;
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
	ft_putstr_fd(all->def_cmd, STDERR_FILENO);
	if (!(get_path(all, extract_env(all->env, "PATH"), all->def_cmd)))
	{
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	ms_export(t_all *all)
{
	char	**args;
	char	*tmp;
	int		i;

	i = 0;
	args = all->args.args;
	while (args[i])
		i++;
	return (0);
}
