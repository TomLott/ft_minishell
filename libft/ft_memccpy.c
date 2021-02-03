/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:41:19 by itollett          #+#    #+#             */
/*   Updated: 2020/11/06 10:42:45 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*newdest;
	unsigned char	*temp;
	size_t			i;

	i = 0;
	newdest = (unsigned char*)dst;
	temp = (unsigned char*)src;
	while (i < n)
	{
		newdest[i] = temp[i];
		if (temp[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
