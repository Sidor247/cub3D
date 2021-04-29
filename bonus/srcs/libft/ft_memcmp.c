/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:06:38 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:30:28 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long	i;
	int				dif;

	i = 0;
	while (i < n)
	{
		dif = (int)(((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		if (dif)
			return (dif);
		i++;
	}
	return (0);
}
