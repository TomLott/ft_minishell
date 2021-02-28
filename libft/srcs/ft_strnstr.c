/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:47:56 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/05 11:08:10 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *ltl, size_t len)
{
	unsigned int	s_len;

	s_len = ft_strlen(ltl);
	if (s_len == 0)
		return ((char *)big);
	while (*big++ && (len-- >= s_len))
		if (!ft_strncmp(big - 1, ltl, s_len))
			return ((char *)(big - 1));
	return (0x0);
}
