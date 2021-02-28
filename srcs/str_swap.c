/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:26:12 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/11 16:12:40 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_swap(char *orig, char *old, int len, char *new_str)
{
	char	*ans;
	char	*tmp[2];
	int		i;
	int		j;

	i = 0;
	while ((orig + i) != old)
		i++;
	orig[i] = '\0';
	j = i + len;
	tmp[0] = ft_strdup(orig);
	tmp[1] = ft_strjoin(tmp[0], new_str);
	free(tmp[0]);
	tmp[0] = ft_strdup(orig + j);
	ans = ft_strjoin(tmp[1], tmp[0]);
	free(tmp[1]);
	free(tmp[0]);
	return (ans);
}
