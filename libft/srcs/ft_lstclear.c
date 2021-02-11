/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:12:52 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/11 14:37:01 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*f)(void *))
{
	t_list	*next;

	if (lst == 0x0 || f == 0x0)
		return ;
	printf("A GDEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, f);
		*lst = next;
	}
}
