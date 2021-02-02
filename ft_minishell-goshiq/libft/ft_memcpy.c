/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:16:13 by itollett          #+#    #+#             */
/*   Updated: 2020/11/02 21:04:55 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*orig;
	unsigned char	*dst_new;
	size_t			i;

	orig = (unsigned char *)src;
	dst_new = (unsigned char *)dst;
	i = 0;
	if (n == 0 || dst_new == orig)
		return (dst);
	while (n-- > 0)
	{
		dst_new[i] = orig[i];
		i++;
	}
	return (dst);
}
