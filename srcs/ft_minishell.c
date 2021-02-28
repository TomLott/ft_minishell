/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:59:45 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/28 13:59:46 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				hook_continue(t_all *all, t_pipi *pp, int j)
{
	if (j < 2)
		g_ex_code = manage_cmds(all);
	else
	{
		if ((all->err = do_pipe(all, pp)))
			return (all->err);
	}
	dup2(all->fd1_def, 1);
	dup2(all->fd0_def, 0);
	free_pipi(&pp);
	return (0);
}

int				hook_command(char *com, t_all *all)
{
	char	**temp;
	int		j;
	char	*point;
	t_pipi	*pp;

	j = -1;
	if ((ft_change_pipes(all, com) != E_DEF) || !(temp = ft_split(com, -10)))
		return ((all->err = E_SYNTAX));
	pp = 0x0;
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
		if ((ft_parse_argument(all->arg, all, &(all->args))) || (ft_fd(all)))
			return (all->err);
		pipi_add_back(&pp, pipi_new(all));
	}
	return (hook_continue(all, pp, j));
}

int				ft_parse_commands(t_all *all)
{
	char	**commands;
	int		i;
	char	*temp;

	i = -1;
	if ((ft_dollar(all, all->line) == 1) || (ft_parse_line(all->line) == -1))
		return ((all->err = E_SYNTAX));
	commands = ft_split(all->line, -1);
	while (commands[++i])
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
			return (1);
	}
	free_double_char(&commands);
	return (0);
}

int				get_data(t_all *all, int *flag)
{
	int			i;

	if (*flag == 0)
		exit(0);
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
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return (-1);
	init_all(&all);
	all->env = copy_env(env);
	all->exec = extract_env(all->env, "PWD");
	while (1)
	{
		signal(SIGINT, myint);
		signal(SIGQUIT, myint);
		g_f[1] = 0;
		g_f[2] = 0;
		get_data(all, &flag);
		if (all->err != E_DEF)
			do_error(all);
		all->err = E_DEF;
	}
}
