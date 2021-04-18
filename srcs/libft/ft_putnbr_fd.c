/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:25:51 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:34:47 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putdigit(long n, int fd)
{
	char	c;

	if (n / 10)
		putdigit(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, sizeof(char));
}

void	ft_putnbr_fd(int n, int fd)
{
	long	longn;

	longn = (long)n;
	if (longn < 0)
	{
		write(fd, "-", sizeof(char));
		longn *= -1;
	}
	putdigit(longn, fd);
}
