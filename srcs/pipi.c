/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:34:35 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/22 13:21:15 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipi_add_back(t_pipi **lst, t_pipi *p_new)
{
	t_pipi	*tmp;

	tmp = *lst;
	if (!tmp)
		tmp = p_new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = p_new;
	}
}

t_pipi	*pipi_new(t_all *all)
{
	t_pipi *ans;

	if (!(ans = malloc(sizeof(t_pipi))))
		do_error(all, "malloc error\n", 6);
	ans->cmd = ft_strdup(all->def_cmd);
	ans->args = copy_env(all->args.args);
	ans->fd0 = all->fd0;
	ans->fd1 = all->fd1;
	ans->next = 0x0;
	return (ans);
}
