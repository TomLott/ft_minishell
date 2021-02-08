/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:24:54 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/08 15:42:04 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_env(t_envlst *env, char *key)
{
	t_envlst	*tmp;
	char		*ans;

	tmp = env;
	ans = 0x0;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key))
		{
			ans = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	return (ans);
}

char	*convert_env(char *str)
{
	return (0x0);
}
