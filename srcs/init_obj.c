/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:45:16 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/04 13:30:15 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_envlst **p)
{
	(*p)->key = 0x0;
	(*p)->value = 0x0;
	(*p)->next = 0x0;
}

void	init_obj(void **p, t_cmd type)
{
	if (type == ENV)
		init_env((t_envlst **)p);
}