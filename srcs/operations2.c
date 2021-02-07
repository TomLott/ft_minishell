/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:09:38 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/07 14:18:23 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(t_all *all)
{
	printf("%s\n", all->line);
	if (all->args.args->content && *((char *)all->args.args->content)) {
		if ((chdir(all->args.args->content)))
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	return (0);
}
