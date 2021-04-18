/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:50:36 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/17 19:05:09 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_extension(char *file, char *ex)
{
	char	*dot;
	int		ex_len;

	dot = file;
	ex_len = ft_strlen(ex);
	while (1)
	{
		dot = ft_strchr(dot, '.');
		if (dot == NULL)
			return (0);
		if (ft_strnstr(dot, ex, ex_len) && (int)ft_strlen(dot) == ex_len)
			return (1);
		else
			dot++;
	}
}

int	check_save(char *str)
{
	return (!ft_strncmp(str, "--save", 6) && ft_strlen(str) == 6);
}

int	check_data(t_data *data)
{
	int	i;

	if (data->res.width == -1 || data->res.height == -1)
		return (1);
	if (data->c_color == 0xFF000000 || data->f_color == 0xFF000000)
		return (1);
	i = 0;
	while (i < 5)
	{
		if (data->textures[i].ptr == NULL)
			return (1);
		i++;
	}
	return (0);
}
