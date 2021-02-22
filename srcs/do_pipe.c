/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:59:19 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/22 13:01:25 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pipe(t_all *all, t_pipi *pipi)
{
	int		ff;
	int		pp[2];
	char	**ar[2];


	printf("INSIDE DO_PIPI\n");
	pipe(pp);
	ff = fork();
	if (ff == 0)
	{
		//printf("%s\t0 is :%d\n%s\t1 is :%d\n", l, pp[0], r, pp[1]);
		printf("inside if %s\n", pipi->cmd);
		ar[0] = malloc(sizeof(char *) * 2);
		close(pp[0]);
		dup2(pp[1], 1);
		ar[0][0] = pipi->cmd;
		ar[0][1] = pipi->args[0];
		if (execve(ft_strjoin("/bin/", pipi->cmd), ar[0], all->env) < 0)
			printf(">%s<\terrr 0\n%s\n", pipi->cmd, strerror(errno));
	}
	else
	{
		ar[1] = malloc(sizeof(char *) * 2);
		close(pp[1]);
		wait(&all->last_rv);
		dup2(pp[0], 0);
		printf("try dis\n");
		printf("inside else - %s %s\n", pipi->next->cmd, pipi->next->cmd);
		ar[1][0] = pipi->next->cmd;
		ar[1][1] = pipi->next->args[0];
		if (execve(ft_strjoin("/bin/", pipi->next->cmd), ar[1], all->env) < 0)
			printf(">%s<\terrr 1\n%s\n", *ar[1], strerror(errno));
	}
}
