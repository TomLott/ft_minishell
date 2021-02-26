/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:54:27 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/26 10:20:59 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_envlst **env)
{
	free((*env)->key);
	free((*env)->value);
	free(*env);
}

void	print_error(t_all *all)
{
	if (all->err == E_SYNTAX)
		ft_putstrn_fd("syntax error", all->fd1);
	else if (all->err == E_READ)
		ft_putstrn_fd("read error", all->fd1);
	else if (all->err == E_MALLOC)
		ft_putstrn_fd("malloc error", all->fd1);
	else if (all->err == E_FD)
		ft_putstrn_fd("no such file or directory", all->fd1);
	else if (all->err == E_PIPE)
		ft_putstrn_fd("syntax error near `|'", all->fd1);
}

void	do_error(t_all *all)
{
	if (!all)
		exit(all->err);
	if (all->err == E_EXIT)
	{
		ft_putstrn_fd("exit", all->fd1);
		exit(0);
	}
	else
		print_error(all);
}
