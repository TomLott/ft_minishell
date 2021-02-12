/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dol_question.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:19:59 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/12 11:26:42 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	convert_dol_question(t_all *all, char *line, int *i)
{
	char	*temp[4];

	*i += 1;
	temp[0] = ft_strdup(line);
	temp[1] = ft_itoa(all->last_rv);
	temp[2] = ft_strdup(line + *i);
	temp[3] = ft_strjoin(temp[0], temp[1]);
	free(temp[0]);
	free(temp[1]);
	temp[0] = ft_strjoin(temp[3], temp[2]);
	if (all->line)
		free(all->line);
	free(temp[2]);
	free(temp[3]);
	all->line = temp[0];
	return (0);
}
