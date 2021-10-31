/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:42:42 by cwhis             #+#    #+#             */
/*   Updated: 2020/11/16 22:08:16 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*p;

	if (!s1)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	p = malloc((len1 + len2 + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	p = p + len1 + len2;
	*p = '\0';
	while (len2--)
	{
		p--;
		*p = *(s2 + len2);
	}
	while (len1--)
	{
		p--;
		*p = *(s1 + len1);
	}
	return (p);
}
