/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 12:58:15 by itollett          #+#    #+#             */
/*   Updated: 2020/11/03 19:33:36 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_comp(char *str, char *ndl, size_t len)
{
	while (*ndl && len)
	{
		if (*str != *ndl)
			return (0);
		str++;
		ndl++;
		len--;
	}
	if (*ndl)
		return (0);
	return (1);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*temp;

	if (!needle[0] || (haystack == needle))
		return ((char *)haystack);
	if (ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	i = 0;
	while (*haystack && len)
	{
		if (*haystack == *needle)
		{
			temp = (char *)haystack;
			if (ft_comp((char *)temp, (char *)needle, len))
				return (temp);
		}
		haystack++;
		len--;
	}
	return (NULL);
}
