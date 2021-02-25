/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:48:22 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/25 15:23:17 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir		*ft_lstnew_r(void *content, int redir)
{
	t_redir	*ans;

	if (0x0 == (ans = malloc(sizeof(t_redir))))
		return (0x0);
	ans->redir = redir;
	ans->next = 0x0;
	ans->cont = content;
	return (ans);
}

void		ft_lstadd_back_r(t_redir **lst, t_redir *new)
{
	t_redir	*prev;

	if (*lst == 0x0)
	{
		*lst = new;
		return ;
	}
	prev = *lst;
	while (prev->next)
		prev = prev->next;
	prev->next = new;
}

int			func_do_trick(char **args, t_all *all)
{
	int		i;
	char	*res[2];

	i = -1;
	res[0] = ft_strdup("");
	while (args[++i])
	{
		if (args[i][0] == -1 || args[i][0] == -2 || args[i][0] == -3)
		{
			res[1] = args[i++];
			if (!args[i])
				return (1);
			ft_lstadd_back_r(&all->l_red, ft_lstnew_r(args[i], res[1][0]));
		}
		else
		{
			(i) ? (res[0] = ft_realloc_r(res[0], -5)) : NULL;
			res[1] = res[0];
			res[0] = ft_strjoin(res[0], args[i]);
			free(res[1]);
		}
	}
	free(all->arg);
	all->arg = ft_strdup(res[0]);
	//all->args.args = ft_split(all->arg, -5);
	return (0);
}

int			ft_parse_argument(char *line, t_all *all, t_args *args)
{
	int	i;
	int	flag;

	(void)args;
	i = 0;
	flag = 0;
	if (!line)
		return (1);
	line = line_cleaner(all->arg);
	all->args.args = ft_split(line, -5);
	func_do_trick(all->args.args, all);
	return (0);
}


int			ft_check_redir(char *line, t_all *all)
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

char		*wrap_zero(char **t, int i)
{
	char	*ans;

	(*t)[i] = '\0';
	ans = *t;
	return (ans);
}

char        *ft_com_parser(char *l, t_all *all, char *t)
{
	int i[2];

	i[0] = 0;
	while(l[all->cmd_len] && l[all->cmd_len] != ' ')
	{
		if (l[all->cmd_len] == '\\' && l[all->cmd_len + 1] && ++all->cmd_len)
			t[i[0]++] = l[all->cmd_len++];
		else if (l[all->cmd_len] == '\"' && ++all->cmd_len)
		{
			while (l[all->cmd_len] && l[all->cmd_len] != '\"')
				t[i[0]++] = l[all->cmd_len++];
			(l[all->cmd_len] == '\"') ? all->cmd_len++ : (i[1] = -1);
		}
		else if (l[all->cmd_len] == '\'' && ++all->cmd_len)
		{
			while (l[all->cmd_len] && l[all->cmd_len] != '\'')
				t[i[0]++] = l[all->cmd_len++];
			(l[all->cmd_len] == '\'') ? all->cmd_len++ : (i[1] = -1);
		}
		else if (ft_check_redir(l, all))
			break;
		else
			t[i[0]++] = l[all->cmd_len++];
	}
	//t[i[0]] = '\0';
	return (i[1] == -1 ) ? "ERROR" : wrap_zero(&t, i[0]);
}

void		get_command(char *s, t_all *all)
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
