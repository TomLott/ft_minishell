/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:21:08 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/24 09:59:22 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_not_line(char c)
{
	char	*temp;

	temp = malloc(4);
	temp[0] = -5;
	temp[1] = c;
	temp[2] = -5;
	temp[3] = '\0';
	ft_lstadd_front(&pnts, ft_lstnew(temp));
	return (temp);
}

void		free_redir(t_redir **red)
{
	t_redir	*tmp;
	t_redir	*prev;

	prev = 0x0;
	tmp = *red;
	while (tmp)
	{
		if (prev)
			free(prev);
		free(tmp->cont);
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev)
		free(prev);
}

int			print_empty_export(char **env)
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

int			file_exists(char *file_path)
{
	struct stat	buffer;

	return (stat(file_path, &buffer) == 0);
}
