/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 00:40:47 by igorlebedev       #+#    #+#             */
/*   Updated: 2021/04/09 14:27:42 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*ntmp;
	t_list	*tmp;
	t_list	*new;

	if (lst == NULL)
		return (NULL);
	nlst = ft_lstnew((*f)(lst->content));
	if (nlst == NULL)
		return (NULL);
	tmp = lst->next;
	ntmp = nlst;
	while (tmp)
	{
		new = ft_lstnew((*f)(tmp->content));
		if (new == NULL)
		{
			ft_lstclear(&nlst, del);
			return (NULL);
		}
		ntmp->next = new;
		ntmp = new;
		tmp = tmp->next;
	}
	return (nlst);
}
