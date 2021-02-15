/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:21:08 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/15 19:27:20 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_empty_export(char **env)
{
	int	i;

	i = 0;
	while (env[i++])
	{
		ft_putstr_fd("declare -x ", STDIN_FILENO);
		ft_putstr_fd(env[i - 1], STDIN_FILENO);
		ft_putstr_fd("\n", STDIN_FILENO);
	}
	return (0);
}
