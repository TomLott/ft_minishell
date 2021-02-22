/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:59:19 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/22 17:21:02 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_all_work(t_pipi *pipi, t_all *all)
{
	while(pipi)
	{
		pipi->args = arr_append(pipi->args, pipi->cmd);
		if (execve(ft_strjoin("/bin/", pipi->cmd), pipi->args, all->env) < 0)
			printf(">%s<\terrr 0\n%s\n", pipi->cmd, strerror(errno));
		pipi = pipi->next;
	}
	printf("done\n");
}

void	fill_pipes(t_all *all, t_pipi *pipi)
{
	int	i;
	int	pp[2];

	i = 0;
	while (i++ < all->pipe)
	{
		pipe(pp);
		dup2(pipi->fd1, pp[0]);
		dup2(pipi->next->fd0, pp[1]);
		close(pp[0]);
		close(pp[1]);
		pipi = pipi->next;
	}
}

void	do_pipe(t_all *all, t_pipi *pipi)
{
	int	i;
	int	f;

	i = 0;
	fill_pipes(all, pipi);
	while (i < all->pipe)
	{
		f = fork();
		if (!f)
		{
			dup2(pipi->fd1, 1);
			pipi->args = arr_append(pipi->args, pipi->cmd);
			if (execve(ft_strjoin("/bin/", pipi->cmd), pipi->args, all->env) < 0)
				printf(">%s<\terrr 0\n%s\n", pipi->cmd, strerror(errno));
		}
		else
			pipi = pipi->next;
	}
	/*
	printf("pipes = %d\n", all->pipe);
	pipe(pp);
	ff[0] = fork();
	if (ff[0] == 0)
	{
	//	close(pp[0]);
		dup2(pp[1], 1);
		//pipi->args = arr_append(pipi->args, pipi->cmd);
		//if (execve(ft_strjoin("/bin/", pipi->cmd), pipi->args, all->env) < 0)
		//	printf(">%s<\terrr 0\n%s\n", pipi->cmd, strerror(errno));
	}
	else
	{
	//	close(pp[1]);
		//wait(&all->last_rv);
		dup2(pp[0], 0);
		//pipi->next->args = arr_append(pipi->next->args, pipi->next->cmd);
		//if (execve(ft_strjoin("/bin/", pipi->next->cmd), pipi->next->args, all->env) < 0)
			//printf(">%s<\terrr 1\n%s\n", pipi->next->cmd, strerror(errno));
	}
	*/
}
