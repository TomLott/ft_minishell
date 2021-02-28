/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:34:35 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/28 13:57:41 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipi(t_pipi **pp)
{
	t_pipi	*tmp;
	t_pipi	*prev;

	tmp = *pp;
	prev = 0x0;
	while (tmp)
	{
		if (prev)
			free(prev);
		free(tmp->cmd);
		free_double_char(&(tmp->args));
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev)
		free(prev);
}

void	pipi_add_back(t_pipi **lst, t_pipi *p_new)
{
	t_pipi	*tmp;

	if (!(*lst))
		*lst = p_new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = p_new;
	}
}

t_pipi	*pipi_new(t_all *all)
{
	t_pipi *ans;

	if (!(ans = malloc(sizeof(t_pipi))))
	{
		all->err = E_MALLOC;
		do_error(all);
	}
	ans->cmd = ft_strdup(all->def_cmd);
	ans->args = copy_env(all->args.args);
	ans->fd0 = all->fd0;
	ans->fd1 = all->fd1;
	ans->next = 0x0;
	ft_lstadd_front(&g_pnts, ft_lstnew(ans));
	return (ans);
}
