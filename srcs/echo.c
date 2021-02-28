/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:12:18 by itollett          #+#    #+#             */
/*   Updated: 2021/02/28 15:12:19 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_flag(char *line)
{
	int		i;

	i = 0;
	if (line[i] == '-')
	{
		i++;
		while (line[i] == 'n')
			i++;
	}
	if (line[i])
		return (1);
	return (0);
}

void	echo_continue(char *temp, int fl, t_all *all)
{
	if (fl)
	{
		if (temp)
			ft_putstr_fd(temp, all->fd1);
		else
			ft_putstr_fd("", all->fd1);
	}
	else
	{
		if (temp)
			ft_putstrn_fd(temp, all->fd1);
		else
			ft_putstrn_fd("", all->fd1);
	}
}

int		ms_echo(t_all *all)
{
	char	*temp;
	int		fl;
	int		i;

	temp = all->arg;
	fl = 0;
	i = -1;
	if (all->args.args)
	{
		while (all->args.args[++i])
		{
			if (!ft_get_flag(all->args.args[i]) && (fl = 1))
				temp += ft_strlen(all->args.args[i]) + 1;
			else
				break ;
		}
	}
	echo_continue(temp, fl, all);
	return (0);
}
