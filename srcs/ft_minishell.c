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
//	printf("%s parse line\n", line);
	return (1);
}

int		ft_do_right_r(t_all *all, t_redir *red)
{
	if (all->fd1 != 1)
		close(all->fd1);
	if (red->redir == -1)
	{
		if (!(all->fd1 = open(red->cont, O_CREAT | O_WRONLY, 0755)))
			return (1);
	}
	if (red->redir == -3)
	{
		if (!(all->fd1 = open(red->cont, O_CREAT | O_APPEND | O_WRONLY, 0755)))
			return (1);
	}
	return (0);
}

int		ft_do_left_r(t_all *all, t_redir *red)
{
	if (!(all->fd0 = open(red->cont, O_RDONLY)))
		return (1);
	return (0);
}

void		ft_fd(t_all *all)
{
	t_redir *redir;

	redir = all->l_red;
	all->fd1 = 1;
	all->fd0 = 0;
	while(redir)
	{
		if (all->l_red->redir == -1 || all->l_red->redir == -3)
			ft_do_right_r(all, redir);
		else if (all->l_red->redir == -2)
			ft_do_left_r(all, redir);
		redir = redir->next;
	}
}

void        hook_command(char *com, t_all *all)
{
	char **temp;
	int j;
	char *point;

	j = 0;
	if (ft_change_pipes(com) == -1)
		do_error(all, 5);
	//printf("%s here is com\n", com);
	temp = ft_split(com, -1);
	while(temp[j])
    {
	    point = temp[j];
	    temp[j] = ft_strtrim(temp[j], " ");
	    free(point);
        refresh_all(&all, &all->args);
		if (ft_change_redir(&temp[j]) == -1)
			do_error(all, 5); /**syntax error*/
		get_command(temp[j], all);
		if (all->cmd_len + 1 < (int)ft_strlen(temp[j]))
		    all->arg = ft_strdup(temp[j] + all->cmd_len);
		ft_parse_argument(all->arg, all, &(all->args));
		//all->args.src = ft_quotes_deleting(all->args.src, all);
		//all->args.dst = ft_quotes_deleting(all->args.dst, all);
		//printf("j is = %d; command is = %i; argument is = %s\n", j, all->cmd, all->arg);
		//printf("args->dst = %s, args->src = %s\n", all->args.dst, all->args.src);
		ft_fd(all);
		all->last_rv = manage_cmds(all);
		
		/*
		if (all->args.args)
		    while(*all->args.args){
		        printf("%s args\n", *all->args.args++);
		    }
			*/
		j++;
	}
}

int ft_parse_commands(t_all *all)
{
	char **commands;
	int i;
	char *temp;

	i = 0;
	if (ft_dollar(all, all->line) == 1)
		do_error(all, 5);	
	if (ft_parse_line(all->line) == -1)
		do_error(all, 5);
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
	ft_parse_commands(all);
	if (all->line)
		free(all->line);
}

int main(int argc, char **argv, char **env)
{
	t_all *all;

	all = 0x0;
	(void)argc;
	(void)argv;
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
