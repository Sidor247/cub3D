/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 20:15:27 by cwhis             #+#    #+#             */
/*   Updated: 2020/11/16 21:29:22 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		p = malloc(sizeof(char));
		*p = '\0';
		return (p);
	}
	if ((ft_strlen(s) - start) < len)
		len = ft_strlen(s) - start;
	p = malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(p + i) = *(s + start + i);
		i++;
	}
	*(p + i) = '\0';
	return (p);
}
