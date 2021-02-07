/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:45:16 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/07 13:59:35 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_all **all)
{
	(*all)->env = 0x0;
	(*all)->line = 0x0;
	(*all)->cmd = DEF;
	(*all)->arg = 0x0;
	(*all)->redir = 0;
	(*all)->cmd_len = 0;
	(*all)->pipe = 0;
	(*all)->grbg = 0x0;
	(*all)->err = E_DEF;
//	(*all)->args = 0x0;
	(*all)->last_rv = 0;
}

void	init_env(t_envlst **p)
{
	(*p)->key = 0x0;
	(*p)->value = 0x0;
	(*p)->next = 0x0;
}

void	init_obj(void **p, t_cmd type)
{
	if (type == ALL)
		init_all((t_all **)p);
	else if (type == ENV)
		init_env((t_envlst **)p);
}
