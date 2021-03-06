/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:40:32 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/30 01:35:47 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	mini_dda(t_vector ray, t_vector pos, char **map)
{
	t_dda	dda;
	int		flag;

	dda_init(&dda, ray, pos);
	while (map[dda.mapPoint.y][dda.mapPoint.x] != '1')
	{
		if (dda.sideDistX < dda.sideDistY)
		{
			dda.sideDistX += dda.deltaDistX;
			dda.mapPoint.x += dda.stepX;
			flag = 1;
		}
		else
		{
			dda.sideDistY += dda.deltaDistY;
			dda.mapPoint.y += dda.stepY;
			flag = 0;
		}
	}
	if (flag)
		return ((dda.mapPoint.x - pos.x + (1 - dda.stepX) / 2) / ray.x);
	else
		return ((dda.mapPoint.y - pos.y + (1 - dda.stepY) / 2) / ray.y);
}

void	put_stripe(t_image *img, int x, int height, int color)
{
	char	*dst;
	int		i;
	int		finish;

	if (height > img->res.height)
		height = img->res.height;
	i = (img->res.height - height) / 2;
	finish = img->res.height - i;
	while (i < finish)
	{
		dst = img->addr + i * img->line_length
			+ x * (img->bits_per_pixel / 8);
		*(unsigned int *)dst = color;
		i++;
	}
}

int	get_height(t_vector ray, t_vector pos, t_data *data, int *color)
{
	float	dist;
	char	side;
	int		height;

	dist = dda(ray, pos, data->map, &side);
	if (side == 'H')
	{
		if (ray.x > 0)
			*color = RED;
		else
			*color = BLUE;
	}
	if (side == 'V')
	{
		if (ray.x > 0)
			*color = GREEN;
		else
			*color = WHITE;
	}
	height = (int)(data->res.height / dist);
	return (height);
}
