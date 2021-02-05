/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:01:24 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/04 15:04:04 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (!s)
        return (NULL);
	while (*(s + i))
	{
		if (*(s + i) == c)
			return ((char *)(s + i));
		i++;
	}
	if (*(s + i) == c)
		return ((char *)(s + i));
	return (0x0);
}
