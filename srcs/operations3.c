/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:47:59 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/18 10:08:01 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(t_all *all)
{
	if (all->arg)
		ft_putstrn_fd(all->args.args[0], STDIN_FILENO);
	else
		ft_putstrn_fd("", STDIN_FILENO);
	return (0);
}
