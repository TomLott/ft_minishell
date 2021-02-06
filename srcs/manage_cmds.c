/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:11:06 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/06 21:58:53 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_cmds(t_all *all)
{
	if (all->cmd == ENV)
		ms_env(all);
	else if (all->cmd == UNSET)
	{
		ms_unset(all);
		ms_env(all);
	}
	else if (all->cmd == PWD)
		ms_pwd();
}
