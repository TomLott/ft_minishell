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
/*
void	do_pipe(t_all *all, char *l, char *r)
{
	int		ff;
	int		pp[2];
	char	**ar[2];

	pipe(pp);
	ff = fork();
	if (ff == 0)
	{
		printf("%s\t0 is :%d\n%s\t1 is :%d\n", l, pp[0], r, pp[1]);
		ar[0] = malloc(sizeof(char *) * 2);
		close(pp[0]);
		dup2(pp[1], 1);
		ar[0][0] = l;
		ar[0][1] = 0x0;
		if (execve(ft_strjoin("/bin/", l), ar[0], all->env) < 0)
			printf(">%s<\terrr 0\n%s\n", l, strerror(errno));
	}
	else
	{
		ar[1] = malloc(sizeof(char *) * 2);
		close(pp[1]);
		wait(&all->last_rv);
		dup2(pp[0], 0);
		ar[1][0] = r;
		ar[1][1] = 0x0;
		if (execve(ft_strjoin("/bin/", r), ar[1], all->env) < 0)
			printf(">%s<\terrr 1\n%s\n", *ar[1], strerror(errno));
	}
}
*/
