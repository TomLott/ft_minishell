/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:33:18 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/08 14:27:31 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	unsigned int		i;

	i = 0;
	str1 = s1;
	str2 = s2;
	while (i++ < n)
		if (*(str1 + i - 1) != *(str2 + i - 1))
			return (*(str1 + i - 1) - *(str2 + i - 1));
	return (0);
}
