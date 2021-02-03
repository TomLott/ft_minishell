/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 11:58:42 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/06 12:48:34 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length(int n)
{
	int	ans;

	ans = 1;
	if (n < 0)
		ans++;
	while (n /= 10)
		ans++;
	return (ans);
}

char		*ft_itoa(int n)
{
	int		length;
	char	*ans;
	char	ch;

	length = get_length(n);
	if (0x0 == (ans = malloc(sizeof(char) * (length + 1))))
		return (0x0);
	*(ans + length) = '\0';
	if (n < 0)
		*ans = '-';
	if (!n)
		*ans = '0';
	while (n)
	{
		length--;
		ch = n % 10;
		if (ch < 0)
			ch *= -1;
		*(ans + length) = ch + 48;
		n /= 10;
	}
	return (ans);
}
