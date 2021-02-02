/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:51:50 by itollett          #+#    #+#             */
/*   Updated: 2020/11/04 10:06:31 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *temp;
	t_list *new_list;

	if (!lst || !f)
		return (NULL);
	if (!(new_list = ft_lstnew(f(lst->content))))
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	temp = new_list;
	lst = lst->next;
	while (lst)
	{
		if (!(new_list = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&temp, del);
			ft_lstclear(&lst, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&temp, new_list);
	}
	return (temp);
}
