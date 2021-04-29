/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:58:08 by cwhis             #+#    #+#             */
/*   Updated: 2020/11/09 19:28:48 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	char	*a;
	int		flag;

	flag = 0;
	p = (char *)s;
	while (*p)
	{
		if (*p == (char)c)
		{
			flag = 1;
			a = p;
		}
		p++;
	}
	if (*p == (char)c)
	{
		flag = 1;
		a = p;
	}
	if (flag)
		return (a);
	return (NULL);
}
