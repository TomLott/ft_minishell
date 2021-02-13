/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:44:34 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/12 12:08:52 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_all *all, char *path, char *ex_name)
{
	char	**dirs;
	char	**args;
	char	*tmp;
	int		i;

	if (!(dirs = ft_split(path, ':')) || !(args = ft_split(all->arg, -2)))
		return (0);
	i = 0;
	while (dirs[i++])
	{
		tmp = ft_strjoin(dirs[i - 1], ex_name);
	}
	//printf("PATH IS:\n%s\nbin is:\n%s\narg[0] is: %s\n", path, ex_name, args[0]);
	free(path);
	return (0x0);
}
