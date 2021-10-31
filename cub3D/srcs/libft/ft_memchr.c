/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:54:56 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:30:00 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned long	i;
	void			*p;

	i = 0;
	p = (void *)s;
	while (i < n)
	{
		if (((unsigned char *)p)[i] == (unsigned char)c)
			return (p + i);
		i++;
	}
	return (NULL);
}
