/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:12:34 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:44:19 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (*(set + i))
	{
		if (c == *(set + i))
			return (1);
		i++;
	}
	return (0);
}

static size_t	trim_length(char const *s1, char const *set)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (check_char(*(s1 + i), set))
	{
		i++;
		if (*(s1 + i) == '\0')
			return (0);
		count++;
	}
	i = ft_strlen(s1) - 1;
	while (check_char(*(s1 + i), set) && i)
	{
		i--;
		count++;
	}
	return (ft_strlen(s1) - count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (!s1)
		return (NULL);
	p = malloc((trim_length(s1, set) + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (check_char(*(s1 + i), set))
		i++;
	while (j < trim_length(s1, set))
	{
		*(p + j) = *(s1 + i);
		i++;
		j++;
	}
	*(p + j) = '\0';
	return (p);
}
