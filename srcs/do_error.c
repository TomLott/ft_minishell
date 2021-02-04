/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:54:27 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/04 15:13:01 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_error(t_all *all)
{
	t_list	*tmp;

	if (!all || !(all->grbg))
		exit(-1);
	while (all->grbg)
	{
		tmp = all->grbg->next;
		free(all->grbg->content);
		free(all->grbg);
		all->grbg = tmp;
	}
}
