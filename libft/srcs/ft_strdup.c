/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:12:58 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/25 15:54:59 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*ans;
	unsigned char	len;

	len = ft_strlen(s);
	if (0x0 == (ans = malloc(sizeof(char) * len + 1)))
		return (0x0);
	*(ans + len) = '\0';
	while (len--)
	{
		*(ans + len) = *(s + len);
	}
	ft_lstadd_back(&pnts, ft_lstnew(ans));
	return (ans);
}
