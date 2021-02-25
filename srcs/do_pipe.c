/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:59:19 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/25 18:03:57 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	do_all_work(t_pipi *pipi, t_all *all)
{
	while (pipi)
	{
		pipi->args = arr_append(pipi->args, pipi->cmd);
		if (execve(ft_strjoin("/bin/", pipi->cmd), pipi->args, all->env) < 0)
			printf(">%s<\terrr 0\n%s\n", pipi->cmd, strerror(errno));
		pipi = pipi->next;
	}
	printf("done\n");
}*/

void	fill_pipes(t_all *all, t_pipi *pipi)
{
	int	i;
	int	pp[2];

	i = 0;
	while (i++ < all->pipe)
	{
		pipe(pp);
		if (pipi->fd1 == 1)
			pipi->fd1 = dup(pp[1]);
		if (pipi->next->fd0 == 0)
			pipi->next->fd0 = dup(pp[0]);
		close(pp[0]);
		close(pp[1]);
		pipi = pipi->next;
	}
}

void	do_pipe(t_all *all, t_pipi *pipi)
{
	int		i;
	int		f;
	t_pipi	*temp;
	int		temp_fd;

	i = 0;
	fill_pipes(all, pipi);
	temp = pipi;
	temp_fd = -2;
	while (i++ <= all->pipe)
	{
		printf("fd0: %d\tfd1: %d\n", pipi->fd0, pipi->fd1);
		f = fork();
		if (!f)
		{
			printf("%s cmd here\n", pipi->cmd);
			dup2(pipi->fd1, 1);
			dup2(pipi->fd0, 0);
			if (temp_fd != -2)
				close(temp_fd);
			pipi->args = arr_append(pipi->args, pipi->cmd);
			if (execve(ft_strjoin("/bin/", pipi->cmd), pipi->args, all->env) < 0)
				printf(">%s<\terrr 0\n%s\n", pipi->cmd, strerror(errno));
		}
		else
		{
			close(pipi->fd1);
			wait(&all->last_rv);
		}
		close(pipi->fd0);
		//close(pipi->fd1);
		//temp_fd = pipi->fd1;
		pipi = pipi->next;
	}
	close(temp_fd);
	i = 0;
	pipi = temp;
	/*while (i++ < all->pipe)
	{
		close(temp->fd1);
		close(temp->fd0);
		temp = temp->next;
	}*/
	dup2(all->fd1_def, 1);
	dup2(all->fd0_def, 0);
}
