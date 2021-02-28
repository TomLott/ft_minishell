/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:48:22 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/28 13:52:42 by jmogo            ###   ########.fr       */
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
	ft_lstadd_front(&pnts, ft_lstnew(ans));
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
	all->arg = ft_strdup(res[0]);
	all->args.args = ft_split(all->arg, -5);
	return (0);
}

char		*wrap_zero(char **t, int i)
{
	char	*ans;

	(*t)[i] = '\0';
	ans = *t;
	return (ans);
}

char		*ft_com_parser(char *l, t_all *all, char *t)
{
	int i[2];

	i[0] = 0;
	while (l[all->cmd_len] && l[all->cmd_len] != ' ')
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
			break ;
		else
			t[i[0]++] = l[all->cmd_len++];
	}
	return (i[1] == -1) ? "ERROR" : wrap_zero(&t, i[0]);
}
