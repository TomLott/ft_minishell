/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:09:38 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/14 19:38:54 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_export(t_all *all)
{
	char	**args;
	int		i;

	if (!ft_strchr(all->def_cmd, '='))
		return (0);
	check_and_add(all->loc_env, all->def_cmd);
	if (all->args.args)
		args = all->args.args;
	i = 0;
	while (args[i++])
	{
		if (!ft_strchr(all->def_cmd, '='))
			return (0);
		check_and_add(all->loc_env, args[i - 1]);
	}
	return (1);
}

void	show_cd_err(t_all *all)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(all->args.args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	cd_set_home(t_all *all)
{
	char	*tmp;

	tmp = extract_env(all->env, "HOME");
	if (0 > (chdir(tmp)))
		show_cd_err(all);
	free(tmp);
}

int		check_path(t_all *all)
{
	if (all->args.args && all->args.args[0])
		return (1);
	cd_set_home(all);
	return (0);
}

int		ms_cd(t_all *all)
{
	if (check_path(all))
		if (0 > (chdir(all->args.args[0])))
			show_cd_err(all);
	set_old_pwd(all);
	printf("HERE\n");
	set_pwd(all);
	return (0);
}
