/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 00:04:23 by igorlebedev       #+#    #+#             */
/*   Updated: 2021/04/09 14:24:31 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*current;

	if (!*lst)
		return ;
	current = *lst;
	next = current->next;
	ft_lstdelone(current, del);
	while (next)
	{
		current = next;
		next = current->next;
		ft_lstdelone(current, del);
	}
	*lst = NULL;
}
