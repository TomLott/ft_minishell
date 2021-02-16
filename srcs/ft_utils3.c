/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:21:08 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/16 16:44:38 by jmogo            ###   ########.fr       */
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
		ft_putstrn_fd(env[i - 1], STDIN_FILENO);
	}
	return (0);
}

int	file_exists(char *file_path)
{
	struct stat	buffer;

	return (stat(file_path, &buffer) == 0);
}
