#include "minishell.h"

int				ft_parse_line(char *line)
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
			return (-1);
		if (line[i] == ';')
			line[i] = -1;
		i++;
	}
	return (1);
}

int				ft_do_right_r(t_all *all, t_redir *red, int temp)
{
	if (temp != 1)
		close(temp);
	if (red->redir == -1)
	{
		if (!(all->fd1 = open(red->cont, O_CREAT | O_WRONLY, 0755)))
			return (-1);
	}
	else if (red->redir == -3)
	{
		if (!(all->fd1 = open(red->cont, O_CREAT | O_APPEND | O_WRONLY, 0755)))
			return (-1);
	}
	return (all->fd1);
}

int				ft_do_left_r(t_all *all, t_redir *red, int temp)
{
	printf("ft_do_left_r\n");
	if (temp != 0)
		close(temp);
	if (!(all->fd0 = open(red->cont, O_RDONLY, 0755)))
	{
		printf("fd0 error\n");
		return (-1);
	}
	return (all->fd0);
}

int				ft_fd(t_all *all)
{
	t_redir	*redir;
	int		temp_in;
	int		temp_out;

	redir = all->l_red;
	temp_in = 0;
	temp_out = 1;
	while (redir)
	{
		printf("args: %d %s\n", redir->redir, redir->cont);
		if (redir->redir == -2)
			temp_in = ft_do_left_r(all, redir, temp_in);
		if (redir->redir == -1 || redir->redir == -3)
			temp_out = ft_do_right_r(all, redir, temp_out);
		redir = redir->next;
	}
	if (all->fd0 >= 0 && all->fd1 >= 1)
	{
		dup2(all->fd0, 0);
		dup2(all->fd1, 1);
	}
	else
		return ((all->err = E_FD));
	return (0);
}

char			*wrap_null(char *ans, char **str)
{
	free(*str);
	*str = 0x0;
	return (ans);
}

char			*ft_get_line(char **s)
{
	int		i;
	int		len;
	char	*temp;
	char	*ret;

	i = 0;
	while (*(*s + i) && *(*s + i) != -10)
		i++;
	len = ft_strlen(*s);
	*(*s + i) = '\0';
	temp = *s;
	if (!(ret = ft_strdup(*s)))
		return (NULL);
	if (i == len)
		return (wrap_null(ret, s));
	if (*(*s + i + 1))
	{
		if (!(*s = ft_strdup((*s + i + 1))))
			return (NULL);
		free(temp);
	}
	else
		*s = NULL;
	temp = NULL;
	return (ret);
}

int				hook_command(char *com, t_all *all)
{
	char	**temp;
	int		j;
	char	*point;
	t_pipi	*pp;

	j = -1;
	if (ft_change_pipes(all, com) != E_DEF)
		return ((all->err = E_SYNTAX));
	pp = 0x0;
	temp = ft_split(com, -10);
	while (temp[++j])
	{
		point = temp[j];
		temp[j] = ft_strtrim(temp[j], " ");
		free(point);
		refresh_all(&all, &all->args);
		if (ft_change_redir(all, &temp[j]) != E_DEF)
			return ((all->err = E_SYNTAX));
		get_command(temp[j], all);
		if (all->cmd_len + 1 < (int)ft_strlen(temp[j]))
			all->arg = ft_strdup(temp[j] + all->cmd_len);
		ft_parse_argument(all->arg, all, &(all->args));
		if (ft_fd(all))
			return (1);
		pipi_add_back(&pp, pipi_new(all));
	}
	if (j < 2)
		all->last_rv = manage_cmds(all);
	else
		do_pipe(all, pp);
	dup2(all->fd1_def, 1);
	dup2(all->fd0_def, 0);
	free_pipi(&pp);
	return (0);
}

int				ft_parse_commands(t_all *all)
{
	char	**commands;
	int		i;
	char	*temp;

	i = 0;
	if (ft_dollar(all, all->line) == 1)
		return ((all->err = E_SYNTAX));
	if (ft_parse_line(all->line) == -1)
		return ((all->err = E_SYNTAX));
	commands = ft_split(all->line, -1);
	while (commands[i])
	{
		all->fd1 = 1;
		all->fd0 = 0;
		all->fd0_def = dup(0);
		all->fd1_def = dup(1);
		refresh_all(&all, &(all->args));
		temp = commands[i];
		commands[i] = ft_strtrim(commands[i], " ");
		free(temp);
		if (hook_command(commands[i], all))
			do_error(all);
		i++;
	}
	free_double_char(&commands);
	return (0);
}

int				get_data(t_all *all, int *flag)
{
	int			i;

	if (*flag == 0)
		exit (0);
	if (g_f[1] == 0)
		ft_print_capt(STDOUT_FILENO, 0);
	if (0 > (i = get_next_line(STDIN_FILENO, &all->line)))
		return ((all->err = E_READ));
	if (!i)
		ft_putstr_fd("exit\n", all->fd1);
	else
		g_f[1] = 1;
	*flag = i;
	process_tilda(all);
	ft_parse_commands(all);
	if (all->line)
		free(all->line);
	return (0);
}

int				main(int argc, char **argv, char **env)
{
	t_all	*all;
	int		flag;

	all = 0x0;
	flag = -2;
	(void)argc;
	(void)argv;
	//do_malloc(all, (void **)(&all), ALL);
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return (-1);
	all->env = copy_env(env);
	while (1)
	{
		signal(SIGINT, myint);
		signal(SIGQUIT, myint);
		g_f[1] = 0;
		g_f[2] = 0;
		get_data(all, &flag);
		if (all->err != E_DEF)
			do_error(all);
	}
}
