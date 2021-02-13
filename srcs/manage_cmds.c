/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:11:06 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/13 20:37:11 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_cmds(t_all *all)
{
	if (all->cmd == ENV)
		return (ms_env(all));
	else if (all->cmd == UNSET)
		return (ms_unset(all));
	else if (all->cmd == EXPORT)
		return (ms_export(all));
	else if (all->cmd == PWD)
		return (ms_pwd());
	else if (all->cmd == CD)
		return (ms_cd(all));
	else if (all->cmd == EXIT)
		return (do_error(all, 0));
	else
		return (ms_def(all));
}
