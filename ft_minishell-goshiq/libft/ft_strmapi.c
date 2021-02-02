/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:40:08 by itollett          #+#    #+#             */
/*   Updated: 2020/11/01 16:55:31 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*temp;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	if (!(temp = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s[i])
	{
		temp[i] = (*f)((unsigned int)i, s[i]);
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
