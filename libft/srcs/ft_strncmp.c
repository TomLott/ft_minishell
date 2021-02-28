/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:04:42 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/04 15:06:34 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int		i;

	i = 0;
	while (i++ < n)
	{
		if (!*(s1 + i - 1) && !*(s2 + i - 1))
			break ;
		if (*(s1 + i - 1) != *(s2 + i - 1))
			return (*((unsigned char *)s1 + i - 1) -
		*((unsigned char *)s2 + i - 1));
	}
	return (0);
}
