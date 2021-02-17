#include "minishell.h"

char *ft_realloc_r(char *str, char c)
{
	char *temp;
	size_t size;

	if (!str[0])
	{
		temp = malloc(2);
		temp[0] = c;
		temp[1] = '\0';
		return (temp);
	}
	size = ft_strlen(str); /**ft_strlen*/
	temp = malloc(size + 1);
	temp = strcpy(temp, str); /**ft_strcopy*/
	temp[size] = c;
	temp[size + 1] = '\0';
	free(str);
	return (temp);
}

char *ft_redir_make(char *line, char c)
{
	int size;
	char *temp;

	if (!line[0])
	{
		temp = malloc(4);
		temp[0] = -5;
		temp[1] = c;
		temp[2] = -5;
		temp[3] = '\0';
	}
	size = ft_strlen(line);
	temp = malloc(size + 3);
	temp = strcpy(temp, line);
	temp[size] = -5;
	temp[size + 1] = c;
	temp[size + 2] = ' ';
	temp[size + 3] = '\0';
	free(line);
	return (temp);
}

static int check_flag_r(char c, int flag, int *i)
{
	if (c == -3)
		(*i)++;
	if (c == '\'' && flag == 2)
	{
		flag = 0;
		(*i)++;
	}
	if (c == '\"' && flag == 1)
	{
		flag = 0;
		(*i)++;
	}
	return (flag);
}

char	*line_cleaner(char *line)
{
	int i;
	int flag;
	char *temp;

	i = 0;
	temp = ft_strdup("");
	while(line[i])
	{
		flag = 0;
		if (line[i] == -1 || line[i] == -2 || line[i] == -3)
			temp = ft_redir_make(temp, line[i++]);
		else if (line[i] == '\\' && ++i)
			temp = ft_realloc_r(temp, line[i++]);
		else if (line[i] == '\"' && (flag = 1))
			while(line[++i] && line[i] != '\"')
				temp = ft_realloc_r(temp, line[i]);
		else if (line[i] == '\'' && (flag = 2))
			while(line[++i] && line[i] != '\'')
				temp = ft_realloc_r(temp, line[i]);
		else if (line[i] == ' ' && ++i)
				temp = ft_realloc_r(temp, -5);
		else
			temp = ft_realloc_r(temp, line[i++]);
		if ((flag = check_flag_r(line[i], flag, &i)))
			return ("Error: qoutes");
	}
	return (temp);
}
