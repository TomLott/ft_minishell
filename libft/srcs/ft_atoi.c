/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:06:25 by jmogo             #+#    #+#             */
/*   Updated: 2020/12/06 11:17:22 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			minus;
	int			ans;
	const char	*tmp;

	tmp = nptr;
	ans = 0;
	minus = 1;
	while (*tmp == ' ' || *tmp == '\t' || *tmp == '\n' ||
		*tmp == '\r' || *tmp == '\v' || *tmp == '\f')
		tmp++;
	if (*tmp == '-' || *tmp == '+')
	{
		if (*tmp == '-')
			minus = -1;
		tmp++;
	}
	while (*tmp >= 48 && *tmp <= 57)
	{
		ans = ans * 10 + *tmp - 48;
		tmp++;
	}
	return (ans * minus);
}
