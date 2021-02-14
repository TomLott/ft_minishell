/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 10:19:45 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/14 19:25:28 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_and_add(char **env, char *to_add)
{
	char	*str[2];

	if (!get_key_value(to_add, &str[0], &str[1]))
	{
		if (check_key(env, str[0]))
			env = pop_str(env, str[0]);
		env = arr_append(env, to_add);
		free_arr((void **)str, 2);
	}
}

int		get_key_value(char *str, char **key, char **value)
{
	char	*temp;
	char	*store;

	temp = ft_strdup(str);
	store = temp;
	if (!(temp = ft_strchr(temp, '=')))
		return (1);
	*temp++ = '\0';
	if (!(*key = ft_strdup(store)))
		return (1);
	if (!(*value = ft_strdup(temp)))
		return (1);
	free(store);
	return (0);
}

char	*extract_env(char **env, char *key)
{
	char		**tmp;
	char		*ans[3];

	tmp = env;
	ans[2] = 0x0;
	while (*tmp)
	{
		get_key_value(*tmp, &ans[0], &ans[1]);
		if (ft_strcmp(key, ans[0]))
		{
			ans[2] = ft_strdup(ans[1]);
			break ;
		}
		tmp++;
	}
	free_arr((void **)&ans, 2);
	return (ans[2]);
}
