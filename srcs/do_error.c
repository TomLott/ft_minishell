/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:54:27 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/08 11:49:07 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_envlst **env)
{
	free((*env)->key);
	free((*env)->value);
	free(*env);
}

int		do_error(t_all *all, int rv)
{
	t_list	*tmp;

	if (!all || !(all->grbg))
		exit(rv);
	while (all->grbg)
	{
		tmp = all->grbg->next;
		free(all->grbg->content);
		free(all->grbg);
		all->grbg = tmp;
	}
	exit(rv);
	return (0);
}
