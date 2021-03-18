/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:00:21 by jmogo             #+#    #+#             */
/*   Updated: 2021/03/18 13:20:38 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_parse_dollar_sec(char **str, char *line, int *i, t_all *all)
{
	char	*for_join;

	for_join = ft_strdup(line + (*i));
	if (all->line && str[1])
		all->line = ft_strjoin(all->line, str[1]);
	all->line = ft_strjoin(all->line, for_join);
	return (0);
}

int			ft_parse_dollar(t_all *all, char *line, int *i)
{
	int		j;
	int		k;
	int		fl;
	char	*str[2];

	fl = 0;
	line[(*i)++] = '\0';
	if (!(k = 0) && line[*i] == '\?')
		return (convert_dol_question(all, line, i));
	if (line[(*i)] == '{' && ++(*i))
		fl = 1;
	j = (*i);
	while (ft_allowed_chars(line[(*i)]))
		(*i)++;
	if (fl == 1 && line[(*i)] != '}')
		return (1);
	if ((*i) - j == 0)
		(*i)--;
	line[(*i)] = '\0';
	str[0] = (char *)malloc(sizeof(char) * ((*i) - j + 1));
	if (line[*i + 1])
		(*i)++;
	while (line[j])
		str[0][k++] = line[j++];
	str[0][k] = '\0';
	str[1] = extract_env(all->env, str[0]);

	return (ft_parse_dollar_sec(str, line, i, all));
}

int			ft_dollar(t_all *all, char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '\'' && (flag = 1))
			flag = get_flag(line, &i, '\'');
		if ((line[i] && line[i] == '\0') || flag == 1)
			return (1);
		if (line[i] == '$')
			ft_parse_dollar(all, line, &i);
		if (line[i])
			i++;
	}
	line[i] = '\0';
	return (0);
}
