/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:08:51 by itollett          #+#    #+#             */
/*   Updated: 2021/02/02 10:10:31 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        refresh_all(t_all **all)
{
    (*all)->cmd = DEF;
    (*all)->arg = NULL;
    (*all)->redir = 0;
    (*all)->cmd_len = 0;
    (*all)->pipe = 0;
}

void        ft_print_capt(int fd)
{
    char *caption;

    caption = "minishell:";
    ft_putstr_fd(caption, fd);
}
