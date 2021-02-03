/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:26:01 by itollett          #+#    #+#             */
/*   Updated: 2020/11/03 18:40:40 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*temp;
	int				i;

	i = 0;
	temp = (unsigned char *)arr;
	while (n > 0)
	{
		if (*(temp + i) == (unsigned char)c)
			return (temp + i);
		i++;
		n--;
	}
	return (NULL);
}
