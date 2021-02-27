/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:47:59 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/27 11:12:40 by jmogo            ###   ########.fr       */
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
	if (i == len && i != 0)
		return (sign * res);
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(num, 2);
		ft_putstr_fd(": ", 2);
		ft_putstrn_fd("numeric argument required", 2);
		return (255);
	}
}

int ms_exit(t_all *all)
{
	int code;
	int i;

	code = 0;
	i = 0;
	if (all->args.args)
	{
		code = stup_atoi(all->args.args[0]);
		return (code);
	}
	if (ex_code)
		code = ex_code;
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
		args = arr_append(args, ft_strdup("minishell"));
		tmp = ft_strjoin(all->exec, ft_strdup("/minishell"));
		if (0 > execve(tmp, args, all->env))
		{
			ft_putstrn_fd(strerror(errno), STDERR_FILENO);
			exit (errno);
		}
		return (errno);
	}
	else
	{
		wait(&ex_code);
		return (1);
	}
}
