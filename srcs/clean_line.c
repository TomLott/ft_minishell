#include "minishell.h"

char			*ft_realloc_r(char *str, char c)
{
	char		*temp;
	size_t		size;

	if (c == ' ')
		c = -5;
	if (!str[0])
	{
		temp = malloc(2);
		temp[0] = c;
		temp[1] = '\0';
		ft_lstadd_front(&g_pnts, ft_lstnew(temp));
		return (temp);
	}
	size = ft_strlen(str);
	if (str[size - 1] == -5 && c == -5)
		return (str);
	temp = malloc(size + 2);
	ft_lstadd_front(&g_pnts, ft_lstnew(temp));
	ft_strcpy(temp, str);
	temp[size] = c;
	temp[size + 1] = '\0';
	free(str);
	return (temp);
}

char			*ft_redir_make(char *line, char c)
{
	int		size;
	char	*temp;

	if (!line[0])
		ft_not_line(c);
	size = ft_strlen(line);
	temp = malloc(size + 3);
	ft_lstadd_front(&pnts, ft_lstnew(temp));
	ft_strcpy(temp, line);
	if (temp[size - 1] != -5)
	{
		temp[size] = -5;
		temp[size + 1] = c;
		temp[size + 2] = -5;
		temp[size + 3] = '\0';
	}
	else
	{
		temp[size] = c;
		temp[size + 1] = -5;
		temp[size + 2] = '\0';
	}
	free(line);
	return (temp);
}

static int		check_flag_r(char *c, int flag, int *i)
{
	if (c[(*i) - 1] == -5 && c[(*i)] == ' ')
		while (c[*i] == ' ')
			(*i)++;
	if (c[*i] == -3)
		(*i)++;
	if (c[*i] == '\'' && flag == 2)
	{
		flag = 0;
		(*i)++;
	}
	if (c[*i] == '\"' && flag == 1)
	{
		flag = 0;
		(*i)++;
	}
	return (flag);
}

void			wrap_temp(t_all *all, char **temp, char *line, int *i)
{
	*temp = ft_realloc_r(*temp, line[*i]);
	line[*i] ? (*i)++ : (all->err = E_SYNTAX);
}

char			*line_cleaner(char *line, t_all *all, char *temp)
{
	int		i[2];

	i[0] = 0;
	while (line[i[0]] && !(i[1] = 0))
	{
		if (line[i[0]] == -1 || line[i[0]] == -2 || line[i[0]] == -3)
			temp = ft_redir_make(temp, line[i[0]++]);
		else if (line[i[0]] == '\\' && ++i[0])
			wrap_temp(all, &temp, line, &i[0]);
		else if (line[i[0]] == '\"' && (i[1] = 1))
			while (line[++i[0]] && line[i[0]] != '\"')
				temp = ft_realloc_r(temp, line[i[0]]);
		else if (line[i[0]] == '\'' && (i[1] = 2))
			while (line[++i[0]] && line[i[0]] != '\'')
				temp = ft_realloc_r(temp, line[i[0]]);
		else
			temp = ft_realloc_r(temp, line[i[0]++]);
		if ((i[1] = check_flag_r(line, i[1], &i[0])))
		{
			(all->err = E_SYNTAX);
			return ("Error:quotes");
		}
	}
	return (temp);
}
