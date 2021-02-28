/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 10:06:51 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/13 10:17:35 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(void **arr, int size)
{
	int	i;

	i = 0;
	while (i++ < size)
		if (arr[i - 1])
			free(arr[i - 1]);
}

void	free_double_char(char ***arr)
{
	int		i;

	i = 0;
	while ((*arr) && (*arr)[i++])
	{
		free((*arr)[i - 1]);
		(*arr)[i - 1] = 0x0;
	}
	free((*arr));
	(*arr) = 0x0;
}
