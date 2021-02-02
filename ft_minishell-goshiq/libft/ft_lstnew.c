/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:36:08 by itollett          #+#    #+#             */
/*   Updated: 2020/11/01 18:36:51 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *temp;

	if (!(temp = malloc(sizeof(t_list))))
		return (NULL);
	temp->content = ft_strdup(content);
	free(content);
	temp->next = NULL;
	return (temp);
}
