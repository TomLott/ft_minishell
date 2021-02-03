/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:21:07 by itollett          #+#    #+#             */
/*   Updated: 2020/11/06 10:44:35 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*str;

	str = (char *)s;
	len = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return (&str[len]);
	if ((*s) == '\0')
		return (NULL);
	while (len > 0)
	{
		if (str[len] == (unsigned char)c)
			return (&str[len]);
		len--;
	}
	if (str[len] == (unsigned char)c)
		return (&str[len]);
	return (NULL);
}
