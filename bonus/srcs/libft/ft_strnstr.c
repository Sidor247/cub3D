/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 17:34:49 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:43:10 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	i = 0;
	while (*(haystack + i) && i < len)
	{
		j = 0;
		if (*(haystack + i) == *(needle + j))
		{
			while (i + j < len && *(haystack + j + i) == *(needle + j))
			{
				j++;
				if (*(needle + j) == '\0')
					return ((char *)(haystack + i));
			}
		}
		i++;
	}
	return (NULL);
}
