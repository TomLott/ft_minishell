/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:46:56 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/25 14:49:22 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	s_len;
	char			*ans;

	if (s == 0x0)
		return (0x0);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		ans = ft_strdup("");
		return (ans);
	}
	if (0x0 == (ans = malloc(sizeof(char) * len + 1)))
		return (0x0);
	*(ans + len) = '\0';
	s_len = 0;
	while (s_len < len && s[s_len])
	{
		ans[s_len] = s[start + s_len];
		s_len++;
	}
	ft_lstadd_back(&g_pnts, ft_lstnew(ans));
	return (ans);
}
