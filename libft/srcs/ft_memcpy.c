/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:22:19 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/03 19:34:03 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int		i;
	unsigned char		*l_dest;
	const unsigned char	*l_src;

	i = 0;
	l_dest = dest;
	l_src = src;
	if (l_dest == 0x0 && l_src == 0x0)
		return (0x0);
	while (i < n)
	{
		*(l_dest + i) = *(l_src + i);
		i++;
	}
	return (l_dest);
}
