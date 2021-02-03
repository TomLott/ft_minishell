/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:13:49 by jmogo             #+#    #+#             */
/*   Updated: 2020/12/06 10:32:33 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*get_word(char *s, char c)
{
	unsigned int	len;
	char			*ans;

	len = 0;
	while (*(s + len) && *(s + len) != c)
		len++;
	if (0x0 == (ans = malloc(sizeof(char) * (len + 1))))
		return (0x0);
	*(ans + len) = '\0';
	while (len--)
		*(ans + len) = *(s + len);
	return (ans);
}

static int			fill_arr(char **ans, char *s, char c)
{
	unsigned int	word;

	word = 0;
	while (*s && *s == c)
		s++;
	while (*s && *s != c)
	{
		if (0x0 == (ans[word] = get_word(s, c)))
		{
			while (word--)
				free(ans[word]);
			return (0);
		}
		word++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	ans[word] = 0x0;
	return (1);
}

static unsigned int	calc_w(char *s_tmp, char c)
{
	unsigned int	isword;
	unsigned int	words;

	isword = 0;
	words = 0;
	while (*s_tmp)
	{
		if (*s_tmp == c && isword)
		{
			words++;
			isword = 0;
		}
		else if (*s_tmp != c)
			isword = 1;
		s_tmp++;
	}
	if (isword)
		words++;
	return (words);
}

char				**ft_split(const char *s, char c)
{
	unsigned int	words;
	char			**ans;

	if (s == 0x0)
		return (0x0);
	words = calc_w((char *)s, c);
	if (0x0 == (ans = malloc(sizeof(char *) * (words + 1))))
		return (0x0);
	if (!fill_arr(ans, (char *)s, c))
		return (0x0);
	return (ans);
}
