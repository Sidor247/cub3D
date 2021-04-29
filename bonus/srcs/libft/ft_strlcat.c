/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:49:03 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:40:58 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dstsize <= dlen)
		return (slen + dstsize);
	i = 0;
	while (i < slen && i < (dstsize - dlen - 1))
	{
		*(dst + dlen + i) = *(src + i);
		i++;
	}
	*(dst + dlen + i) = '\0';
	return (slen + dlen);
}
