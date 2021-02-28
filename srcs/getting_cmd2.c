/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:48:22 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/28 13:55:06 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parse_argument(char *line, t_all *all, t_args *args)
{
	int		i;
	int		flag;
	char	*temp;

	(void)args;
	i = 0;
	flag = 0;
	if (!line)
		return (0);
	temp = line;
	line = line_cleaner(all->arg, all, ft_strdup(""));
	if (all->err != E_DEF)
		return (1);
	free(temp);
	all->args.args = ft_split(line, -5);
	func_do_trick(all->args.args, all);
	return (0);
}

int		ft_check_redir(char *line, t_all *all)
{
	if (line[all->cmd_len] == -3)
	{
		if (line[all->cmd_len + 1] == -3)
			all->redir = 2;
	}
	else if (line[all->cmd_len] == -1)
		all->redir = 1;
	else if (line[all->cmd_len] == -2)
		all->redir = 3;
	else if (line[all->cmd_len] == '|')
		return (1);
	return (all->redir);
}

void	get_command(char *s, t_all *all)
{
	char *temp[2];

	temp[0] = malloc(4096);
	temp[0] = ft_com_parser(s, all, temp[0]);
	temp[1] = temp[0];
	temp[0] = ft_strtrim(temp[0], " ");
	if ((all->def_cmd = ft_strdup(temp[0])) && ft_strcmp(temp[0], "pwd"))
		all->cmd = PWD;
	else if (ft_strcmp(temp[0], "cd"))
		all->cmd = CD;
	else if (ft_strcmp(temp[0], "echo"))
		all->cmd = ECHO;
	else if (ft_strcmp(temp[0], "export"))
		all->cmd = EXPORT;
	else if (ft_strcmp(temp[0], "unset"))
		all->cmd = UNSET;
	else if (ft_strcmp(temp[0], "env"))
		all->cmd = ENV;
	else if (ft_strcmp(temp[0], "exit"))
		all->cmd = EXIT;
	else if (ft_strcmp(temp[0], "minishell"))
		all->cmd = SELF;
	else
		all->cmd = DEF;
	free_arr((void **)&temp, 2);
}
