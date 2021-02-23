/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:08:51 by itollett          #+#    #+#             */
/*   Updated: 2021/02/23 18:03:12 by jmogo            ###   ########.fr       */
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
		if (args->args)
			free_double_char(&(args->args));
		args = args->next;
	}
}

void        refresh_all(t_all **all, t_args *args)
{
	(void)args;
    (*all)->cmd = DEF;
    if ((*all)->arg)
    	free_and_null(&((*all)->arg));
    (*all)->redir = 0;
    (*all)->cmd_len = 0;
	(*all)->l_red = NULL;
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
