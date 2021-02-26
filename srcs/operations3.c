/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:47:59 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/26 20:23:04 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stup_atoi(char *num)
{
	int		i;
	int		res;
	int 	len;
	int		sign;

	res = 0;
	sign = 1;
	i = 0;
	len = ft_strlen(num);
	if ((num[i] == '-' || num[i] == '+') && ++i)
		(num[i - 1] == '-') ? (sign = -1) : 1;
	while (num[i] >= '0' && num[i] <= '9')
		res = res * 10 + (num[i++] - 48);
	if (i == len)
		return (sign * res);
	else
		return (255);
}

int ms_exit(t_all *all)
{
	int code;
	int i;

	code = -1;
	i = 0;
	if (all->args.args)
		code = stup_atoi(all->args.args[0]);
	if (ex_code)
		code = ex_code;
	else
		code = 0;
	return (code);
}


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
