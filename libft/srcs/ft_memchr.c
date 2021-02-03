/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:08:05 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/03 19:36:39 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		symb;
	unsigned int		i;

	str = s;
	symb = c;
	i = 0;
	while (i++ < n)
		if (*(str + i - 1) == symb)
			return (unsigned char *)(str + i - 1);
	return (0x0);
}
