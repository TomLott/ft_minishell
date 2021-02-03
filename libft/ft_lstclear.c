/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:25:55 by itollett          #+#    #+#             */
/*   Updated: 2020/11/02 20:10:02 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *temp;
	t_list *nxt;

	temp = *lst;
	if (del)
	{
		if (temp)
		{
			while (temp)
			{
				nxt = temp->next;
				del((temp)->content);
				free(temp);
				temp = nxt;
			}
			*lst = NULL;
		}
	}
}
