/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:28:16 by itollett          #+#    #+#             */
/*   Updated: 2020/11/01 16:29:33 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int c)
{
	int len;

	len = 0;
	if (c < 0)
	{
		len++;
		c = -c;
	}
	while (c > 0)
	{
		len++;
		c = c / 10;
	}
	return (len);
}

static char	*ft_copy(int temp, int sign, int len)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (temp > 0)
	{
		res[len - i - 1] = temp % 10 + '0';
		temp = temp / 10;
		i++;
	}
	if (sign == 1)
	{
		res[len - i - 1] = '-';
		i++;
	}
	res[len] = '\0';
	return (res);
}

char		*ft_itoa(int n)
{
	char	*result;
	int		len;
	int		temp;
	int		sign;

	temp = n;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = (n < 0) ? 1 : 0;
	len = ft_len(temp);
	temp = (n < 0) ? -temp : temp;
	result = ft_copy(temp, sign, len);
	return (result);
}
