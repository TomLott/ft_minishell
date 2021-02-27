/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:54:27 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/27 16:05:50 by itollett         ###   ########.fr       */
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
	else if (all->err == E_EXIT_ARG)
		ft_putstrn_fd("exit\nexit: too many arguments", all->fd1);
}

void	do_error(t_all *all)
{
	int count;

	count = 0;
	if (!all)
		exit(all->err);
	if (all->args.args)
		while (all->args.args[count])
			count++;
	if (all->err == E_EXIT && count < 2)
	{
		ft_putstrn_fd("exit", all->fd1);
		exit(ex_code);
	}
	else if (all->err == E_EXIT)
		all->err = E_EXIT_ARG;
	else
		print_error(all);
}
