/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:51:38 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/14 10:33:05 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env(t_all *all)
{
	char	**tmp;
	char	*str[2]; /* str[0] = key, str[1] = value */

	tmp = all->env;
	while (*tmp)
	{
		get_key_value(*tmp, &str[0], &str[1]);
		if (str[0])
			ft_putstr_fd(str[0], STDIN_FILENO);
		ft_putstr_fd("=", STDIN_FILENO);
		ft_putstr_fd(str[1], STDIN_FILENO);
		ft_putstr_fd("\n", STDIN_FILENO);
		tmp++;
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
	char		**tmp_env;
	int			i;

	i = 0;
	tmp = all->args.args;
	while (tmp[i++])
		if (check_key(all->env, tmp[i - 1]))
			all->env = pop_str(all->env, tmp[i - 1]);
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
	while (args[i++])
		printf("str is %s\n", args[i - 1]);
	return (0);
}
