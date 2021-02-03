/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:47:14 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/04 08:03:12 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	unsigned int	i;
	unsigned int	ans;

	i = 0;
	if (n <= ft_strlen(dest))
		return (n + ft_strlen(src));
	while (*(dest + i) && i < n)
		i++;
	ans = i + ft_strlen(src);
	while (i < n - 1 && *src)
	{
		*(dest + i) = *src;
		src++;
		i++;
	}
	*(dest + i) = '\0';
	return (ans);
}
