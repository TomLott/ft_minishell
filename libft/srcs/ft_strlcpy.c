/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:09:38 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/17 17:49:51 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcpy(char *dest, char *src)
{
	unsigned int	i;

	i = 0;
	if (dest == 0x0 || src == 0x0)
		return (1);
	while (src[i])
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (0);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (dest == 0x0 || src == 0x0)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	while ((i < (size - 1)) && *(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (ft_strlen(src));
}
