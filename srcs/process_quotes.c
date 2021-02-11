/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:07:23 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/11 19:00:10 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		compare_quotes(char **single, char **doub, char **start, char **finish)
{
	if (!(*single) && !(*doub))
		return (0);
	if (!(*single))
	{
		*start = *doub;
		*finish = ft_strchr(*start + 1, '\'');
	}
	return (1);
}

char	*srch_no_sh(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return 0x0;
	if (*str == c)
		return (str);
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != '\\')
			return (str + i);
		i++;
	}
	return (0x0);
}

int		process_quotes(char **str)
{
	char	*tmp[5];

	if (!(**str))
		return 0;
	tmp[1] = srch_no_sh(*str, '\'');
	tmp[2] = srch_no_sh(*str, '\"');
	if (tmp[1] > tmp[2])
	{
		tmp[0] = tmp[2];
		tmp[3] = ft_strchr(tmp[0] + 1, '\"'); /* don't forget \\ */
		while (tmp[3] && *(tmp[3] - 1) == '\\')
			tmp[3] = ft_strchr(tmp[0] + 1, '\"');
	}
	else
	{
		tmp[0] = tmp[1];
		tmp[3] = ft_strchr(tmp[0] + 1, '\'');
		while (tmp[3] && *(tmp[3] - 1) == '\\')
			tmp[3] = ft_strchr(tmp[0] + 1, '\'');
	}
	//*tmp[0] = '\0';
	//*tmp[3] = '\0';
	printf("%s\n\n%s\n\n", tmp[0], tmp[3]);
	return (0);
}
