/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:40:51 by itollett          #+#    #+#             */
/*   Updated: 2020/11/05 21:01:25 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest1;
	unsigned char	*source;
	size_t			i;

	dest1 = (unsigned char *)dst;
	source = (unsigned char *)src;
	i = -1;
	if (src == dst)
		return (dst);
	if (src > dst)
	{
		while (++i < len)
			dest1[i] = source[i];
	}
	else
	{
		while (len > 0)
		{
			dest1[len - 1] = source[len - 1];
			len--;
		}
	}
	return (dst);
}
