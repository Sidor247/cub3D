/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:27:01 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:19:34 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	n;

	i = 0;
	n = 0;
	sign = 1;
	while (*(str + i) == ' ' || *(str + i) == '\t' || *(str + i) == '\n'
		|| *(str + i) == '\f' || *(str + i) == '\r' || *(str + i) == '\v')
		i++;
	if (*(str + i) == '+' || *(str + i) == '-')
	{
		if (*(str + i) == '-')
			sign = -1;
		i++;
	}
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		n = 10 * n + *(str + i) - '0';
		i++;
	}
	if (sign == -1)
		return ((int)(-n));
	return ((int)(n));
}