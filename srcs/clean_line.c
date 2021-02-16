char	*ft_realloc(char *str, char c)
{
	 char *temp;
	 size_t size;

	 if (!str[0])
	{
		 temp = malloc(3);
		 temp[0] = c;
		 temp[1] = '\0';
		 return (temp);
	}
	size = ft_strlen(str); /**ft_strlen*/
	temp = malloc(size + 1);
	temp = ft_strcpy(temp, str); /**ft_strcopy*/
	temp[size] = c;
	temp[size + 1] = '\0';
	free(str);
	return (temp);
}

char	*ft_redir_make(char *line, char c)
{
	int size;
	char *temp;

	if (!line[0])
	{
		temp = malloc(4);
		temp[0] = ' ';
		temp[1] = c;
		temp[2] = ' ';
		temp[3] = '\0';
	}
	size = ft_strlen(line); /*ft_strlen */
	temp = malloc(size + 3);
	temp = ft_strcpy(temp, line); /**ft_strcopy*/
	temp[size] = ' ';
	temp[size + 1] = c;
	temp[size + 2] = ' ';
	temp[size + 3] = '\0';
	free(line);
	return (temp);
}

char	*line_cleaner(char *line)
{
	int i;
	int j;
	int flag;
	char *temp;

	i = 0;
	j = 0;
	temp = ft_strdup(""); /* make it ft_strdup*/
	while(line[i])
	{
		flag = 0;
		if (line[i] == -1 || line[i] == -2 || line[i] == -3)
		{
			temp = ft_redir_make(temp, line[i]);
			(line[i] == -3) ? i += 2 : i++;
		}
		if (line[i] == '\\' && ++i)
			temp = ft_realloc(temp, line[i++]);			
		else if (line[i] == '\"' && (flag = 1))
		{
			while(line[++i] && line[i] != '\"')
				temp = ft_realloc(temp, line[i++]);
			(line[i++] == '\"') ? flag = 0 : 1;
		}
		else if (line[i] == '\'' && (flag = 1))
		{
			while(line[++i] && line[i] != '\'')
				temp = ft_realloc(temp, line[i]);
			(line[i++] == '\'') ? flag = 0 : 1;
		}
		else
			temp = ft_realloc(temp, line[i++]);
		if (flag == 1)
			return ("Error: qoutes");
	}
	return (temp);
}
