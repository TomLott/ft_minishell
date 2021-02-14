#include "minishell.h"

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
			return (-1);	/** syntax error*/
		if (line[i] == ';')
			line[i] = -1; /** we change semicolons to (-1) by ASCII to split commands by (-1) */
		i++;
	}
	printf("%s parse line\n", line);
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
		all->args.src = ft_quotes_deleting(all->args.src, all);
		all->args.dst = ft_quotes_deleting(all->args.dst, all);
		printf("j is = %d; command is = %i; argument is = %s\n", j, all->cmd, all->arg);
		printf("args->dst = %s, args->src = %s\n", all->args.dst, all->args.src);
		all->last_rv = manage_cmds(all);
		/**if (all->args.args)
		    while(*all->args.args){
		        printf("%s args\n", *all->args.args++);
		    }*/
		j++;
	}
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
//		all->last_rv = manage_cmds(all);
	}
	free_double_char(commands);
	return (1);
}


void get_data(t_all *all)
{

	if ( 0 > get_next_line(STDIN_FILENO, &all->line))
		do_error(all, -1);
	process_tilda(all);
	ft_parse_commands(all, all->line);
	if (all->line)
		free(all->line);
}

int main(int argc, char **argv, char **env)
{
	t_all *all;

	do_malloc(all, (void **)(&all), ALL);
	all->env = copy_env(env);
	//ft_init_env(env, all);
	while(1)
	{
		ft_print_capt(1);
		signal(SIGINT, myint);
		get_data(all);
	//	refresh_all(&all);
	//	break; /*remove*/
	}

}
