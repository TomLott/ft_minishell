/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:08:51 by itollett          #+#    #+#             */
/*   Updated: 2021/02/14 19:34:17 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			arr_len(char **arr)
{
	int	ans;

	ans = 0;
	while (arr && arr[ans])
		ans++;
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
		//free_and_null(&(args->src));
		//free_and_null(&(args->dst));
		//if (args->args)
		//	free_double_char(args->args);
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
	(void)args;
    //args->dst = NULL;
    //args->src = NULL;
	if ((*all)->def_cmd)
		free_and_null(&((*all)->def_cmd));
	free_args(&((*all)->args));
}

void        ft_print_capt(int fd)
{
    char *caption;

    caption = "minishell:";
    ft_putstr_fd(caption, fd);
}
