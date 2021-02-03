/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:43:53 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/07 13:54:59 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int		i;
	unsigned char		*l_dest;
	unsigned char		ch;
	const unsigned char	*l_src;

	i = 0;
	l_dest = dest;
	l_src = src;
	ch = c;
	if (l_dest == 0x0 && l_src == 0x0)
		return (0x0);
	while (i < n)
	{
		*(l_dest + i) = *(l_src + i);
		if (*(l_src + i) == ch)
			return (l_dest + i + 1);
		i++;
	}
	return (0x0);
}
