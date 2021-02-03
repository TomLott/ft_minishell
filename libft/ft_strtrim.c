/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 11:29:53 by itollett          #+#    #+#             */
/*   Updated: 2020/11/06 18:21:59 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		find_start(char *str, char *set)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (set[j] && str[i])
		{
			if (str[i] == set[j])
				break ;
			j++;
		}
		if (j == (int)ft_strlen(set))
			break ;
		i++;
	}
	return (i);
}

int		find_end(char *str, char *set)
{
	int i;
	int j;

	i = ft_strlen(str);
	while (i > 0)
	{
		j = 0;
		while (set[j] && str[i])
		{
			if (str[i] == set[j])
				break ;
			j++;
		}
		if (j == (int)ft_strlen(set))
			break ;
		i--;
	}
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*str;
	int		len;

	i = -1;
	if (!s1 || !set)
		return (NULL);
	start = find_start((char *)s1, (char *)set);
	end = find_end((char *)s1, (char *)set);
	if (start > end)
		return (ft_strdup(""));
	if (!(str = (char *)malloc(sizeof(char) * (end - start + 1))))
		return (NULL);
	len = end - start;
	while (++i < len)
	{
		str[i] = s1[start];
		start++;
	}
	str[i] = '\0';
	return (str);
}
