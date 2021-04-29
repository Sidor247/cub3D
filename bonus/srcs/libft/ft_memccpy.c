/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:27:01 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:29:41 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned long	i;

	i = 0;
	while (i < n)
	{
		(*(unsigned char *)(dst + i)) = (*(unsigned char *)(src + i));
		if (*(unsigned char *)(src + i) == (unsigned char)c)
			return ((unsigned char *)(dst + i + 1));
		i++;
	}
	return (NULL);
}
