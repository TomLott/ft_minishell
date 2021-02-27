#include "minishell.h"

int			ft_parse_dollar_sec(char **str, char *line, int *i, t_all *all)
{
	char	*for_join;
	char	*for_free;

	for_join = ft_strdup(line + (*i));
	for_free = all->line;
	if (all->line && str[1])
		all->line = ft_strjoin(all->line, str[1]);
	free(for_free);
	for_free = all->line;
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
	printf("before conv dol\n");
	if (!(k = 0) && line[*i] == '\?')
		return (convert_dol_question(all, line, i));
	printf("after conv dol\n");
	if (line[(*i)] == '{' && ++(*i))
		fl = 1;
	j = (*i);
	while (ft_allowed_chars(line[(*i)]))
		(*i)++;
	if (fl == 1 && line[(*i)] != '}')
		return (1); /**error*/
	if ((*i) - j == 0)
		(*i)--;
	line[(*i)] = '\0';
	str[0] = (char *)malloc(sizeof(char) * ((*i)++ - j + 1));
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
			return (1); /** syntax error*/
		if (line[i] == '$')
			ft_parse_dollar(all, line, &i);
		if (line[i])
			i++;
	}
	return (0);
}
