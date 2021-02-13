/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:08:51 by itollett          #+#    #+#             */
/*   Updated: 2021/02/13 19:36:33 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			arr_len(char **arr)
{
	int	ans;

	ans = 0;
	while (arr && arr[ans])
	{
		printf("ARR IS %s\n", arr[ans]);
		ans++;
	}
	return (ans);
}

void		free_and_null(char **str)
{
	if (*str)
	{
		free(*str);
		*str = 0x0;
	}
}

void		free_args(t_args *args)
{
	while (args)
	{
		args->cmd = DEF;
		args->redir = 0;
		free_and_null(&(args->src));
		free_and_null(&(args->dst));
		//ft_lstclear(&(args->args), &free); /*structure of my dreams*/
		args = args->next;
	}
}

void        refresh_all(t_all **all, t_args *args)
{
    (*all)->cmd = DEF;
    (*all)->arg = NULL;
    (*all)->redir = 0;
    (*all)->cmd_len = 0;
    (*all)->pipe = 0;
    args->dst = NULL;
    args->src = NULL;
	free_args(&((*all)->args));
}

void        ft_print_capt(int fd)
{
    char *caption;

    caption = "minishell:";
    ft_putstr_fd(caption, fd);
}
