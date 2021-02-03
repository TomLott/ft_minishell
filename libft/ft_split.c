/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:52:56 by itollett          #+#    #+#             */
/*   Updated: 2020/11/06 16:13:05 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_counter(const char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int		ft_length(const char *str, char c)
{
	int len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

static char		**ft_mass_clean(char **temp, int count)
{
	int i;

	i = 0;
	while (i < count && temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	return (NULL);
}

static char		**ft_fulfilling(const char *s, char c, int count, char **temp)
{
	int amount;
	int j;
	int len;
	int i;

	amount = 0;
	i = 0;
	while (amount < count)
	{
		while (s[i] == c)
			i++;
		len = ft_length(&s[i], c);
		if (!(temp[amount] = (char *)malloc(sizeof(char) * (len + 1))))
			return (ft_mass_clean(temp, amount));
		j = 0;
		while (j < len)
			temp[amount][j++] = s[i++];
		temp[amount][j] = '\0';
		amount++;
	}
	temp[amount] = NULL;
	return (temp);
}

char			**ft_split(char const *s, char c)
{
	char	**temp;
	int		i;
	int		j;
	int		len;
	int		count;

	len = 0;
	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	count = ft_counter(s, c);
	if (!(temp = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	temp = ft_fulfilling(s, c, count, temp);
	return (temp);
}
