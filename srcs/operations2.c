/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:09:38 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/18 10:11:01 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_export(t_all *all)
{
	char	*str[2];
	int		i;

	if (!ft_strchr(all->def_cmd, '='))
		return (0);
	get_key_value(all->def_cmd, &str[0], &str[1]);
	if (check_key(all->env, str[0]))
		check_and_add(&(all->env), all->def_cmd);
	else
		check_and_add(&(all->loc_env), all->def_cmd);
	free_arr((void **)&str, 2);
	i = 0;
	if (all->arg)
		while (all->args.args[i++])
		{
			get_key_value(all->args.args[i - 1], &str[0], &str[1]);
			if (check_key(all->env, str[0]))
				check_and_add(&(all->env), all->args.args[i - 1]);
			else
				check_and_add(&(all->loc_env), all->args.args[i - 1]);
			free_arr((void **)&str, 2);
		}
	return (1);
}

void	show_cd_err(t_all *all)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(all->args.args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstrn_fd(strerror(errno), STDERR_FILENO);
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
	if (all->arg)
		return (1);
	cd_set_home(all);
	return (0);
}

int		ms_cd(t_all *all)
{
	errno = 0;
	if (check_path(all))
		if (0 > (chdir(all->args.args[0])))
			show_cd_err(all);
	set_old_pwd(all);
	set_pwd(all);
	return (errno);
}
