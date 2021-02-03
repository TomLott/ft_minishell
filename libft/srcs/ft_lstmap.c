/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:20:54 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/07 13:09:07 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ans;
	t_list	*next;

	if (lst == 0x0 || f == 0x0)
		return (0x0);
	ans = 0x0;
	while (lst)
	{
		if (0x0 == (next = ft_lstnew(f(lst->content))) && del)
		{
			ft_lstclear(&next, del);
			return (0x0);
		}
		ft_lstadd_back(&ans, next);
		lst = lst->next;
	}
	return (ans);
}
