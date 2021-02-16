/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:44:06 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/16 16:39:26 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == 0x0)
		return ;
	while (*s++)
		write(fd, s - 1, 1);
}

void	ft_putstrn_fd(char *s, int fd)
{
	if (s == 0x0)
		return ;
	while (*s++)
		write(fd, s - 1, 1);
	ft_putstr_fd("\n", fd);
}
