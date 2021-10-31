/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:43:54 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:32:56 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned long	i;

	if (!(dst || src))
		return (dst);
	i = 0;
	if (src > dst || (unsigned long)(dst - src) > n)
	{
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dst)[n - i - 1]
				= ((unsigned char *)src)[n - i - 1];
			i++;
		}
	}
	return (dst);
}
