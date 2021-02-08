/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:09:38 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/08 16:20:45 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(t_all *all)
{
	if (all->args.args && all->args.args->content)
		if (*((char *)all->args.args->content))
			return (1);
	return (0);
}

int	ms_cd(t_all *all)
{
	printf("%p\n", all->args.args);
	if (all->args.args)
		printf("%s\n", (char *)all->args.args->content);
	if (check_path(all))
//	if (all->args.args->content && *((char *)all->args.args->content)) {
		if (0 > (chdir(all->args.args->content)))
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putstr_fd(all->args.args->content, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
		}
	return (0);
}
