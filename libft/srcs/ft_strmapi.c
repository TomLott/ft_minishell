/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:27:22 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/06 14:33:15 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*ans;

	if (s == 0x0 || f == 0x0)
		return (0x0);
	len = ft_strlen(s);
	if (0x0 == (ans = malloc(sizeof(char) * (len + 1))))
		return (0x0);
	*(ans + len) = '\0';
	while (len--)
		*(ans + len) = f(len, *(s + len));
	return (ans);
}
