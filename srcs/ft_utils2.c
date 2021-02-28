/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:20:54 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/27 11:14:38 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_flag(char *line, int *i, char c)
{
	int flag;

	flag = 1;
	(*i)++;
	while (line[(*i)])
	{
		if (line[(*i)] == '\\' && line[(*i) + 1] && line[(*i) + 1] != '\'')
			(*i) += 2;
		else if (line[(*i)] == c)
			return (0);
		(*i)++;
	}
	return (1);
}

int			ft_change_pipes(t_all *all, char *line)
{
	int i;
	int flag;

	i = -1;
	flag = 0;
	all->pipe = 0;
	while (line[++i])
	{
		if (line[i] == '\\' && line[i + 1] && (i += 2))
			continue ;
		if (line[i] == '\'' && (flag = 1))
			flag = get_flag(line, &i, '\'');
		else if (line[i] && line[i] == '\"' && (flag = 1))
			flag = get_flag(line, &i, '\"');
		if ((line[i] && line[i] == '\0') || flag == 1)
			return ((all->err = E_SYNTAX));
		if (line[i] == '|')
		{
			all->pipe++;
			line[i] = -10;
		}
	}
	if (line[0] && line[i - 1] == -10)
		return ((all->err = E_SYNTAX));
	return (0);
}

int			ft_change_redir(t_all *all, char **line)
{
	int i[2];

	i[0] = -1;
	i[1] = 0;
	while (++i[0] < (int)ft_strlen(*line))
	{
		if (*(*line + i[0]) == '\'' && (i[1] = 1))
			i[1] = get_flag(*line, &(i[0]), '\'');
		else if (*(*line + i[0]) && *(*line + i[0]) == '\"' && (i[1] = 1))
			i[1] = get_flag(*line, &i[0], '\"');
		if ((*(*line + i[0]) && *(*line + i[0]) == '\0') && i[1] == 1)
			return ((all->err = E_SYNTAX));
		if (*(*line + i[0]) == '>')
		{
			if (*(*line + i[0] + 1) && *(*line + i[0] + 1) == '>')
			{
				*(*line + i[0]) = -3;
				*(*line + (i[0]++) + 1) = -3;
			}
			else
				*(*line + i[0]) = -1;
		}
		(*(*line + i[0]) == '<') ? (*(*line + i[0]) = -2) : 1;
	}
	return (0);
}

void		myint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
		ex_code = 130;
		if (g_f[1] == 0)
			ft_print_capt(1, 1);
	}
	if (sig == SIGQUIT)
	{
		if (g_f[2] == 1 && (ex_code = 131))
			ft_putstrn_fd("Quit: 3", 1);
		else
		{
			write(1, "\b\b  \b\b", 6);
			write(1, "\n", 1);
		}
		if (g_f[1] == 0)
			ft_print_capt(1, 1);
	}
}

int			ft_allowed_chars(char c)
{
	int ret;

	ret = 0;
	(c == '_') ? ret = 1 : 1;
	((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) ? ret = 1 : 1;
	(c >= '0' && c <= '9') ? ret = 1 : 1;
	return (ret);
}
