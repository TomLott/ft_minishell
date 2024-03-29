/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:22:36 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/25 14:58:22 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*ans;
	char			*tmp;
	unsigned int	len;

	ft_lstadd_front(&g_pnts, ft_lstnew((char *)s1));
	ft_lstadd_front(&g_pnts, ft_lstnew((char *)s2));
	if (s1 == 0x0 || s2 == 0x0)
		return (0x0);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (0x0 == (ans = malloc(sizeof(char) * len + 1)))
		return (0x0);
	tmp = ans;
	*(ans + len) = '\0';
	while (*(s1++))
		*(tmp++) = *(s1 - 1);
	while (*(s2++))
		*(tmp++) = *(s2 - 1);
	ft_lstadd_front(&g_pnts, ft_lstnew(ans));
	return (ans);
}
