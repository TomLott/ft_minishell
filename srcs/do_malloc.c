/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:04:17 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/04 15:08:58 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_addnewptr(t_all *all, void *p)
{
	t_list	*toadd;

	if (!(toadd = malloc(sizeof(t_list))))
		do_error(all);
	toadd->next = 0x0;
	toadd->content = p;
	if (!(all->grbg))
		all->grbg = toadd;
	else
	{
		toadd->next = all->grbg;
		all->grbg = toadd;
	}
}

void	do_malloc(t_all *all, void **p, t_cmd type)
{
	if (type == ENV)
		*p = malloc(sizeof(t_envlst));
	if (!(*p))
		do_error(all);
	init_obj(p, type);
	ft_addnewptr(all, *p);
}
