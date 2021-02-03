/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:24:24 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/04 07:58:36 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ans;
	unsigned int	calc;

	if (size != 0)
		if (nmemb > (2147483647 / size))
			return (0x0);
	if (nmemb != 0)
		if (size > (2147483647 / nmemb))
			return (0x0);
	calc = nmemb * size;
	if (0x0 == (ans = malloc(calc)))
		return (0x0);
	while (calc--)
		*(ans + calc) = 0;
	return (ans);
}
