/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:53:08 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/16 14:56:38 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, size_t n_size)
{
	char	*temp;
	size_t	size;

	if (!str)
		return (malloc(n_size));
	size = ft_strlen(str);
	if (n_size <= size)
		return (NULL);
	temp = ft_strdup(str);
	temp[n_size] = '\0';
	free(str);
	return (temp);
}
