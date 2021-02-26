/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:47:59 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/26 12:55:38 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(t_all *all)
{
	if (all->arg)
		ft_putstrn_fd(all->arg, all->fd1);
	else
		ft_putstrn_fd("", all->fd1);
	return (0);
}

int	ms_self(t_all *all)
{
	int		id;
	char	**args;
	char	*tmp;

	id = fork();
	if (!id)
	{
		args = 0x0;
		args = arr_append(args, "minishell");
		tmp = ft_strjoin(all->exec, "/minishell");
		if (0 > execve(tmp, args, all->env))
		{
			ft_putstrn_fd(strerror(errno), STDERR_FILENO);
			exit (errno);
		}
		return (errno);
	}
	else
	{
		wait(&(all->last_rv));
		return (1);
	}
}
