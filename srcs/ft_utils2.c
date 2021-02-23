/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:20:54 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/22 15:34:45 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int         get_flag(char *line, int *i, char c)
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

int         ft_change_pipes(t_all *all, char *line)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	all->pipe = 0;
	while (line[i])
	{
		if (line[i] == '\'' && (flag = 1))
			flag = get_flag(line, &i, '\'');
		else if (line[i] && line[i] == '\"' && (flag = 1))
			flag = get_flag(line, &i, '\"');
		if ((line[i] && line[i] == '\0' ) || flag == 1)
			return (-1); /** syntax error*/
		if (line[i] == '|')
		{
			all->pipe++;
			line[i] =  -10;
		}
		i++;
	}
	return (1);
}

char        ft_change_redir(char **line)
{
	int i;
	int flag;

	i = -1;
	flag = 0;
	while (++i < (int)ft_strlen(*line))
	{
		if (*(*line + i) == '\'' && (flag = 1))
			flag = get_flag(*line, &i, '\'');
		else if (*(*line + i) && *(*line + i) == '\"' && (flag = 1))
			flag = get_flag(*line, &i, '\"');
		if ((*(*line + i) && *(*line + i) == '\0') && flag == 1)
			return (-1); /** syntax error*/
		if (*(*line + i) == '>')
        {
		    if (*(*line + i + 1) && *(*line + i + 1) == '>')
			{
                *(*line + i) = -3;
                *(*line + (i++) + 1) = -3;
			}
			else
                *(*line + i) = -1;
		}
		(*(*line + i) == '<') ? (*(*line + i) = -2) : 1;
	}
	return (1);
}

void        myint(int sig) 
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_print_capt(1);
		//signal(SIGINT, myint);
	}
}

int         ft_allowed_chars(char c)
{
    int ret;

    ret = 0;
    (c == '_') ? ret = 1 : 1;
    ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) ? ret = 1 : 1;
    (c >= '0' && c <= '9') ? ret = 1 : 1;
    return (ret);
}
