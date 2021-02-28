/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dol_question.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:19:59 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/27 10:41:40 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				convert_dol_question(t_all *all, char *line, int *i)
{
	char	*temp[4];

	*i += 1;
	printf("ex code is %d\n", g_ex_code);
	temp[0] = ft_strdup(line);
	temp[1] = ft_itoa(g_ex_code);
	temp[2] = ft_strdup(line + *i);
	temp[3] = ft_strjoin(temp[0], temp[1]);
	free(temp[0]);
	free(temp[1]);
	temp[0] = ft_strjoin(temp[3], temp[2]);
	if (all->line)
		free(all->line);
	free(temp[2]);
	free(temp[3]);
	all->line = temp[0];
	return (0);
}

int				check_for_any_grbg(char *line)
{
	int		i;
	int		count;
	char	*set;

	i = 0;
	count = 0;
	set = " /|><\\";
	if (line[0] == '|')
		return (1);
	while (line[i] == ' ')
		i++;
	if ((i == (int)ft_strlen(line)) && i != 0)
		return (0);
	while (line[i])
	{
		if (ft_strchr(set, line[i]))
			count++;
		if (line[i] == '\t')
			return (1);
		i++;
	}
	if ((count == (int)ft_strlen(line)) && count != 0)
		return (1);
	return (0);
}

int				ft_parse_line(char *line)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (check_for_any_grbg(line))
		return (-1);
	while (line[i])
	{
		if (line[i] == '\\' && line[i + 1] && (i += 2))
			continue ;
		if (line[i] == '\'' && (flag = 1))
			flag = get_flag(line, &i, '\'');
		else if (line[i] && line[i] == '\"' && (flag = 1))
			flag = get_flag(line, &i, '\"');
		if (line[i] == '\0' && flag == 1)
			return (-1);
		if (line[i] == ';')
			line[i] = -1;
		i++;
	}
	return (1);
}
