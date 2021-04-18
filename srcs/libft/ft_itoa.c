/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:55:43 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:23:31 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nlen(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	if (n == 0)
		return (++i);
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	fill_str(char *s, long n, int length)
{
	if (n < 0)
	{
		*s = '-';
		n *= -1;
	}
	*(s + length) = '\0';
	if (n == 0)
		*s = '0';
	while (n)
	{
		length--;
		*(s + length) = n % 10 + '0';
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	long	longn;
	int		length;
	char	*s;

	longn = (long)n;
	length = nlen(longn);
	s = malloc((length + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	fill_str(s, n, length);
	return (s);
}
