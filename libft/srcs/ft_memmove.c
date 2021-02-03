/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:53:43 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/03 19:36:16 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int			i;
	unsigned char			*l_dest;
	const unsigned char		*l_src;

	i = 0;
	l_dest = dest;
	l_src = src;
	if (l_dest < l_src)
		while (i++ < n)
			*(l_dest + i - 1) = *(l_src + i - 1);
	else if (l_dest > l_src)
		while (n-- > 0)
			*(l_dest + n) = *(l_src + n);
	return (l_dest);
}
