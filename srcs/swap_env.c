/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 09:39:03 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/13 19:34:39 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(t_all *all)
{
	char	cwd[4096];
	char	**tmp_env;
	char	*str[3];	/* str[0] = key, str[1] = value, str[3] - temp pwd */

	tmp_env = all->env;
	while (*tmp_env)
	{
		get_key_value(*tmp_env, &str[0], &str[1]);
		if (ft_strcmp(str[0], "PWD"))
		{
			all->env = pop_str(all->env, "PWD");
			str[2] = getcwd(cwd, 4096);
			printf("DO NEGO: %s\n", str[2]);
			str[2] = ft_strjoin("PWD=", str[2]);
			all->env = arr_append(all->env, str[2]);
			break ;
		}
		tmp_env++;
	}
}

void	set_old_pwd(t_all *all)
{
	char	**tmp_env;
	char	*str[2];	/* str[0] = key, str[1] = value */
	char	*pwd;

	tmp_env = all->env;
	while (*tmp_env)
	{
		get_key_value(*tmp_env, &str[0], &str[1]);
		if (ft_strcmp(str[0], "OLDPWD"))
		{
			all->env = pop_str(all->env, "OLDPWD");
			pwd = ft_strjoin("OLDPWD=", extract_env(all->env, "PWD"));
			tmp_env = arr_append(all->env, pwd);
			all->env = tmp_env;
			break ;
		}
		tmp_env++;
	}
}
