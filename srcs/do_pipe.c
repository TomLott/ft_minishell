/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:59:19 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/26 13:17:41 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	check_nodes(t_pipi *pipi)
{
	t_pipi	*temp;
	int 	res;

	temp = pipi;
	res = 0;
	if (!temp)
	    res = 1;
	while (temp)
	{
		if (!temp->cmd || !(*temp->cmd))
			return ((res = 1));
		temp = temp->next;
	}
	return (res);
}

int		fill_pipes(t_all *all, t_pipi *pipi)
{
	int	i;
	int	pp[2];
	int res;

	i = 0;
	res = check_nodes(pipi);
	while (i++ < all->pipe && !res)
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
	return (res);
}

int		do_pipe(t_all *all, t_pipi *pipi)
{
	int		i;
	int		f;
	t_pipi	*temp;
	int		temp_fd;

	i = 0;
	if (fill_pipes(all, pipi))
		return ((all->err = E_PIPE));
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
			{
				ft_putstrn_fd(strerror(errno), all->fd1);
				exit(errno);
			}
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
		dup2(all->fd1_def, 1);
		dup2(all->fd0_def, 0);
	}
	close(temp_fd);
	i = 0;
	pipi = temp;
	return (0);
	/*while (i++ < all->pipe)
	{
		close(temp->fd1);
		close(temp->fd0);
		temp = temp->next;
	}*/
}
