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
void ft_init_env(char **env, t_all *all)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	all->env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(env[i])
	{
		//all->env[i] = ft_strdup(env[i]);
		i++;
	}
	all->env[i] = NULL;
}
*/
void myint(int sig) {
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_print_capt(1);
		//signal(SIGINT, myint);
	}
}

int get_flag(char *line, int *i, char c)
{
	int flag;

	printf("we are here = %s\n", line);
	flag = 1;
	(*i)++;
	while (line[(*i)] != c && line[*i + 1])
	{
		(*i)++;
	}
	if (line[(*i)] == c)
		return (0);
	return (1);
}

int ft_parse_line(char *line)
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
		if (line[i] == ';')
			line[i] = -1; /** we change semicolons to (-1) by ASCII to split commands by (-1) */
		i++;
	}
	return (1);
}

void	parse_argument(char *com, t_all *all)
{
	char **temp;

	temp = 0x0;
	/**тут нужно заменить все пробелы между ковычками*/
}

int ft_change_pipes(t_all *all, char *line)
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

char ft_change_redir(char **line)
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

void hook_command(char *com, t_all *all)
{
	char **temp;
	int j;
	char *point;
	t_args *args;

	j = 0;
	args = malloc(sizeof(t_args));
	/**get_command(com, &i, all);
	if (all->cmd_len + 1 < ft_strlen(com))
	{
		all->arg = ft_strdup(com + all->cmd_len);
		ft_change_pipes(all, all->arg);
		temp = ft_split(all->arg, -1);
		parse_argument(com, all);
	}*/
	ft_change_pipes(all, com);
	printf("%s here is com\n", com);
	temp = ft_split(com, -1);
	while(temp[j])
    {
	    point = temp[j];
	    temp[j] = ft_strtrim(temp[j], " ");
	    free(point);
        refresh_all(&all);
		ft_change_redir(&temp[j]);
		get_command(temp[j], all);
		if (all->cmd_len + 1 < ft_strlen(temp[j]))
		    all->arg = ft_strdup(temp[j] + all->cmd_len);
		ft_parse_argument(all->arg, all, args);
		printf("j is = %d; command is = %i; argument is = %s\n", j, all->cmd, all->arg);
		printf("args->dst = %s, args->src = %s\n", args->dst, args->src);
		/*
		if (args->args)
		    while(args->args){
		        printf("%s args\n", args->args->content);
		        args->args = args->args->next;
		    }
		*/
		j++;
	}
	all->args = args->args; /* don't forget to remove */
}

int ft_parse_commands(t_all *all, char *line)
{
	char **commands;
	int i;
	int flag;
	char *temp;

	i = 0;
	if (ft_parse_line(all->line) == -1)
		do_error(all, -1);
	commands = ft_split(all->line, -1);
	while(commands[i])
	{
		refresh_all(&all);
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
		break; /*remove*/
	}

}
