/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:44:06 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/17 17:53:59 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == 0x0)
		return ;
	while (*s++)
	{
		if (*(s - 1) == -5)
			write(fd, " ", 1);
		else
			write(fd, s - 1, 1);
	}
}

void	ft_putstrn_fd(char *s, int fd)
{
	if (s == 0x0)
		return ;
	while (*s++)
	{
		if (*(s - 1) == -5)
			write(fd, " ", 1);
		else
			write(fd, s - 1, 1);
	}
	write(fd, "\n", 1);
}
