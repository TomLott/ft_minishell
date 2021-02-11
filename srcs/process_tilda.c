/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tilda.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:46:15 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/11 16:29:30 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_any_quote(char c)
{
	if (c == 34 || c == 39 || c == 96) /* 34 = ", 39 = ',  96 = ` */
		return (1);
	return (0);
}

int		inside_quotes(char *str, char *end, char c)
{
	int		num;
	char	*tmp;

	num = 0;
	tmp = str;
	while (tmp < end)
	{
		if (*tmp == '\\' && *(tmp + 1))
		{
			tmp += 2;
			continue ;
		}
		else if (*tmp == c)
			num++;
		tmp++;
	}
	if (num % 2)
		return (1); /* it means we are between quotes */
	return (0);
}

int		check_tilda_pos(char *s, char *til)
{
	char	c;

	if (til > s)
	{
		c = *(til - 1);
		if (is_any_quote(c))
			return (1);
		if (inside_quotes(s, til, 34) || inside_quotes(s, til, 39) ||
			inside_quotes(s, til, 96))
			return (1);
	}
	c = *(til + 1);
	if (c == '/' || c == '+' || c == '\0' || ft_isspace(c))
		return (0);
	return (1);
}

void	process_tilda(t_all *all)
{
	char	*tmp;
	char	*head;

	head = all->line;
	while ((tmp = ft_strchr(head, '~')))
	{
		if (check_tilda_pos(head, tmp))
		{
			head = tmp + 1;
			continue ;
		}
		if (*(tmp + 1) == '+')
			all->line = str_swap(all->line, tmp, 2,
								extract_env(all->env, "PWD"));
		else
			all->line = str_swap(all->line, tmp, 1,
								extract_env(all->env, "HOME"));
		head = tmp + 1;
	}
}
