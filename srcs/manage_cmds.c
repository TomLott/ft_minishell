/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:11:06 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/26 20:23:25 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_cmds(t_all *all)
{
    if (all->err != E_DEF)
        return (-1);
	if (all->cmd == ENV)
		return (ms_env(all));
	else if (all->cmd == SELF)
		return (ms_self(all));
	else if (all->cmd == UNSET)
		return (ms_unset(all));
	else if (all->cmd == EXPORT)
		return (ms_export(all));
	else if (all->cmd == PWD)
		return (ms_pwd());
	else if (all->cmd == CD)
		return (ms_cd(all));
	else if (all->cmd == EXIT)
	{
		all->err = E_EXIT;
		ex_code = ms_exit(all);
		do_error(all);
		return (0);
	}
	else if (all->cmd == ECHO)
		return (ms_echo(all));
	else
		return (ms_def(all));
}
