#include "minishell.h"

//int main(int ar, char **argv)
//{
//	pid_t pid = fork();
//	srand(getpid());
//	int t = rand()%4;
//	printf("sleep time=%d pid=%d\n", t, pid);
//	sleep(t);
//	printf("fork() return %d\n", pid);
//
//}
/*
 *
 */
void        myint(int sig) {
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_print_capt(1);
		//signal(SIGINT, myint);
	}
}

int         get_flag(char *line, int *i, char c)
{
	int flag;

	printf("we are here = %s\n", line);
	flag = 1;
	(*i)++;
	while (line[(*i)])
	{
		if (line[(*i)] == '\\' && line[(*i) + 1])
			(*i) += 2;
		else if (line[(*i)] == c)
			return (0);
		(*i)++;
	}
	return (1);
}

int         ft_parse_line(char *line)
{
	int i;
	int flag;

	i = 0;
	flag = 0;

	while (line[i])
	{
		if (line[i] == '\'' && (flag = 1))
			flag = get_flag(line, &i, '\'');
		else if (line[i] && line[i] == '\"' && (flag = 1))
			flag = get_flag(line, &i, '\"');
		if (line[i] == '\0' && flag == 1)
			return (-1); /** syntax error*/
		if (line[i] == ';')
			line[i] = -1; /** we change semicolons to (-1) by ASCII to split commands by (-1) */
		i++;
	}
	printf("%s parse line\n", line);
	return (1);
}

int         ft_change_pipes(t_all *all, char *line)
{
	int i;
	int flag;

	i = 0;
	flag = 0;

	while (line[i])
	{
		if (line[i] == '\'' && (flag = 1))
			flag = get_flag(line, &i, '\'');
		else if (line[i] && line[i] == '\"' && (flag = 1))
			flag = get_flag(line, &i, '\"');
		if ((line[i] && line[i] == '\0' ) || flag == 1)
			return (-1); /** syntax error*/
		if (line[i] == '|')
			line[i] =  -1;
		i++;
	}
	return (1);
}

char        ft_change_redir(char **line)
{
	int i;
	int flag;

	i = 0;
	flag = 0;

	while (i < ft_strlen(*line))
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
                *(*line + i + 1) = -3;
				i++;
			}
			else
                *(*line + i) = -1;
		}
		if (*(*line + i) == '<')
            *(*line + i) = -2;
		i++;
		//printf("%c on the end if cycle\n", *line[i]);
	}
	
	return (1);
}

void        hook_command(char *com, t_all *all)
{
	char **temp;
	int j;
	char *point;

	j = 0;
	ft_change_pipes(all, com);
	printf("%s here is com\n", com);
	temp = ft_split(com, -1);
	while(temp[j])
    {
	    point = temp[j];
	    temp[j] = ft_strtrim(temp[j], " ");
	    free(point);
        refresh_all(&all, &all->args);
		ft_change_redir(&temp[j]);
		get_command(temp[j], all);
		if (all->cmd_len + 1 < ft_strlen(temp[j]))
		    all->arg = ft_strdup(temp[j] + all->cmd_len);
		ft_parse_argument(all->arg, all, &(all->args));
		printf("j is = %d; command is = %i; argument is = %s\n", j, all->cmd, all->arg);
		printf("args->dst = %s, args->src = %s\n", all->args.dst, all->args.src);
		/*if (all->args.args)
		    while(all->args.args){
		        printf("%s args\n", all->args.args->content);
		        all->args.args = all->args.args->next;
		    }*/
		j++;
	}
	//all->args = *args; /* don't forget to remove */
}

int         ft_allowed_chars(char c)
{
    int ret;

    ret = 0;
    (c == '_') ? ret = 1 : 1;
    ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) ? ret = 1 : 1;
    (c >= '0' && c <= '9') ? ret = 1 : 1;
   // (c == '{' || c == '}') ? ret = 1 : 1;
    return (ret);
}

int         ft_parse_dollar(t_all *all, char *line, int *i)
{
    int j;
    int k;
    int fl;
    char *temp;
    char *doll;
    char *for_free;
    char *for_join;

    line[(*i)] = '\0';
    (*i)++;
    fl = 0;
    if (line[(*i)] == '{' && ++(*i))
        fl = 1;
    j = (*i);
    k = j;
    while (ft_allowed_chars(line[(*i)]))
        (*i)++;
    if (fl == 1 && line[(*i)] != '}')
        return (1); /**error*/
	if ((*i) - j == 0)
		(*i)--;
    line[(*i)] = '\0';
    temp = (char *)malloc(sizeof(char) * ((*i) - j + 1));
    (*i)++;
    for_join = ft_strdup(line + (*i));
    k = 0;
    while (line[j])
        temp[k++] = line[j++];
    temp[k] = '\0';
    doll = extract_env(all->env, temp);
    for_free = all->line;
    if (all->line && doll)
		all->line = ft_strjoin(all->line, doll);
    free(for_free);
    for_free = all->line;
    all->line = ft_strjoin(all->line, for_join);
    return (0);

}

int ft_dollar(t_all *all, char *line)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while (line[i])
    {
        if (line[i] == '\'' && (flag = 1))
            flag = get_flag(line, &i, '\'');
        if ((line[i] && line[i] == '\0' ) || flag == 1)
            return (1); /** syntax error*/
        if (line[i] == '$')
            ft_parse_dollar(all, line, &i);
        if (line[i])
			i++;
    }
    return (0);
}

int ft_parse_commands(t_all *all, char *line)
{
	char **commands;
	int i;
	char *temp;

	i = 0;
	ft_dollar(all, all->line);
	if (ft_parse_line(all->line) == -1)
		do_error(all, -1);
	commands = ft_split(all->line, -1);
	while(commands[i])
	{
		refresh_all(&all, &(all->args));
		temp = commands[i];
		commands[i] = ft_strtrim(commands[i], " ");
		hook_command(commands[i], all);
		free(temp);
		i++;
	}
	free(commands);
	return (1);
}


void get_data(t_all *all)
{

	if ( 0 > get_next_line(STDIN_FILENO, &all->line))
		do_error(all, -1);
	//all->line = ft_strdup("echo \"hello;world\""); /*use for test commands. Remove after*/
	process_tilda(all);
	ft_parse_commands(all, all->line);
	//free(line);
}

int main(int argc, char **argv, char **env)
{
	t_all *all;

	do_malloc(all, (void **)(&all), ALL);
	ft_init_env(env, all);
	while(1)
	{
		ft_print_capt(1);
		signal(SIGINT, myint);
		get_data(all);
		all->last_rv = manage_cmds(all);
	//	refresh_all(&all);
	//	break; /*remove*/
	}

}
