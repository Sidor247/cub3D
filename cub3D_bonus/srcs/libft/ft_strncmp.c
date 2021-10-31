/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:31:21 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:42:46 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((*(s1 + i)) && (*(s2 + i)) && i < n
		&& (unsigned char)(*(s1 + i)) == (unsigned char)(*(s2 + i)))
		i++;
	if (i == n)
		i--;
	return ((unsigned char)(*(s1 + i)) - (unsigned char)(*(s2 + i)));
}
