/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:51:38 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/18 10:25:00 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env(t_all *all)
{
	char	*str[2];
	int		i;

	i = 0;
	while (all->env[i++])
	{
		get_key_value(all->env[i - 1], &str[0], &str[1]);
		if (str[0])
			ft_putstr_fd(str[0], STDIN_FILENO);
		ft_putstr_fd("=", STDIN_FILENO);
		ft_putstrn_fd(str[1], STDIN_FILENO);
		free_arr((void **)&str, 2);
	}
	return (0);
}

int	ms_pwd(void)
{
	char	cwd[4096];

	if (!(getcwd(cwd, 4096)))
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (errno);
	}
	else
		ft_putstrn_fd(cwd, STDIN_FILENO);
	return (0);
}

int	ms_unset(t_all *all)
{
	char		**tmp;
	int			i;

	i = 0;
	tmp = all->args.args;
	while (tmp[i++])
	{
		if (check_key(all->env, tmp[i - 1]))
		{
			all->env = pop_str(all->env, tmp[i - 1]);
			continue ;
		}
		if (check_key(all->loc_env, tmp[i - 1]))
			all->loc_env = pop_str(all->loc_env, tmp[i - 1]);
	}
	return (0);
}

int	ms_def(t_all *all)
{
	if (*(all->line) == 0)
		return (0);
	if (is_export(all))
		return (0);
	if (!(get_path(all, extract_env(all->env, "PATH"), all->def_cmd)))
	{
		ft_putstr_fd(all->def_cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (errno);
	}
	return (0);
}

int	ms_export(t_all *all)
{
	char	**args;
	char	*str[3];
	int		i;

	if (!all->arg)
		return (print_empty_export(all->env));
	args = all->args.args;
	i = 0;
	while (args[i++])
	{
		if (ft_strchr(args[i - 1], '='))
		{
			all->env = arr_append(all->env, args[i - 1]);
			continue ;
		}
		if (check_key(all->loc_env, args[i - 1]))
		{
			str[0] = extract_env(all->loc_env, args[i - 1]);
			str[1] = ft_strjoin(args[i - 1], "=");
			str[2] = ft_strjoin(str[1], str[0]);
			all->env = arr_append(all->env, str[2]);
			free_arr((void **)&str, 3);
		}
	}
	return (0);
}
