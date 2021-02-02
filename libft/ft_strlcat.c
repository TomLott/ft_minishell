/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:15:06 by itollett          #+#    #+#             */
/*   Updated: 2020/11/06 19:16:55 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t len;
	size_t i;

	len = ft_strlen(dst);
	i = 0;
	if (size <= len)
		return (size + ft_strlen(src));
	if (size != 0)
	{
		while ((len + i < (size - 1)) && src[i])
		{
			dst[len + i] = src[i];
			i++;
		}
		dst[len + i] = '\0';
	}
	return (ft_strlen(src) + len);
}
