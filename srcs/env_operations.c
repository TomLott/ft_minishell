/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:31:47 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/13 15:47:38 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **arr)
{
	int		len_arr;
	int		i;
	char	**ans[2];

	i = 0;
	len_arr = 0;
	while (arr[len_arr])
		len_arr++;
	if (!(ans[0] = malloc(sizeof(char *) * (len_arr + 1))))
		return (0x0);
	ans[1] = ans[0];
	while (i++ < len_arr)
	{
		*ans[1] = ft_strdup(arr[i - 1]);
		ans[1]++;
	}
	*ans[1] = 0x0;
	return (ans[0]);
}

char	**pop_str(char **arr, char *key)
{
	int		len_arr;
	int		i;
	char	**ans[2];

	i = 0;
	len_arr = 0;
	while (arr[len_arr])
		len_arr++;
	if (!(ans[0] = malloc(sizeof(char *) * len_arr)))
		return (0x0);
	ans[1] = ans[0];
	while (i++ < len_arr)
	{
		if (!(ft_strncmp(arr[i - 1], key, ft_strlen(key))))
			continue ;
		*ans[1] = ft_strdup(arr[i - 1]);
		ans[1]++;
	}
	*ans[1] = 0x0;
	free_double_char(arr);
	return (ans[0]);
}
