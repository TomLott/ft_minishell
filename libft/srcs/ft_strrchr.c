/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:22:49 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/04 15:00:00 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*ans;
	unsigned int	i;

	i = 0;
	ans = 0x0;
	if (!s)
        return (NULL);
	while (*(s + i))
	{
		if (*(s + i) == c)
			ans = (char *)(s + i);
		i++;
	}
	if (*(s + i) == c)
		ans = (char *)(s + i);
	return (ans);
}
