/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:36:01 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:42:08 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	length;
	char	*p;

	if (!s || !f)
		return (NULL);
	length = ft_strlen(s);
	p = malloc((length + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		*(p + i) = f((unsigned int)i, *(s + i));
		i++;
	}
	*(p + length) = '\0';
	return (p);
}
