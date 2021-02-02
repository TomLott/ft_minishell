/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:06:59 by itollett          #+#    #+#             */
/*   Updated: 2020/10/31 16:07:15 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char *temp;

	temp = (unsigned char*)malloc(size * count);
	if (!temp)
		return (NULL);
	else
		ft_bzero(temp, size * count);
	return (temp);
}
