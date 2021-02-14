/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:31:47 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/14 16:16:31 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_key(char **arr, char *key)
{
	int	i;

	i = 0;
	while (arr && arr[i++])
		if (!(ft_strncmp(arr[i - 1], key, ft_strlen(key))))
			return (1);
	return (0);
}

char	**copy_env(char **arr)
{
	int		len_arr;
	int		i;
	char	**ans[2];

	i = 0;
	len_arr = arr_len(arr);
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

char	**arr_append(char **arr, char *to_add)
{
	int		len;
	int		i;
	char	**ans;

	i = 0;
	len = arr_len(arr) + 1;
	if (!(ans = malloc(sizeof(char *) * (len + 1))))
		return (0x0);
	ans[0] = ft_strdup(to_add);
	while (i++ < len - 1)
		ans[i] = ft_strdup(arr[i - 1]);
	ans[len] = 0x0;
	free_double_char(arr);
	return (ans);
}

char	**pop_str(char **arr, char *key)
{
	int		len_arr;
	int		i;
	char	**ans[2];

	i = 0;
	len_arr = arr_len(arr);
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
