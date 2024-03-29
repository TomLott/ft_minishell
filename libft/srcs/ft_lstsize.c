/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 18:59:22 by jmogo             #+#    #+#             */
/*   Updated: 2020/11/06 19:02:14 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	ans;

	ans = 0;
	if (lst == 0x0)
		return (0);
	while (lst)
	{
		lst = lst->next;
		ans++;
	}
	return (ans);
}
