/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:54:04 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/25 23:23:49 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	dda_init(t_dda *dda, t_vector ray, t_vector pos)
{
	dda->deltaDistX = fabsf(1 / ray.x);
	dda->deltaDistY = fabsf(1 / ray.y);
	dda->mapPoint.x = (int)pos.x;
	dda->mapPoint.y = (int)pos.y;
	if (ray.x > 0)
	{
		dda->stepX = 1;
		dda->sideDistX = (ceilf(pos.x) - pos.x) * dda->deltaDistX;
	}
	else
	{
		dda->stepX = -1;
		dda->sideDistX = (pos.x - floorf(pos.x)) * dda->deltaDistX;
	}
	if (ray.y > 0)
	{
		dda->stepY = 1;
		dda->sideDistY = (ceilf(pos.y) - pos.y) * dda->deltaDistY;
	}
	else
	{
		dda->stepY = -1;
		dda->sideDistY = (pos.y - floorf(pos.y)) * dda->deltaDistY;
	}
}

float	dda(t_vector ray, t_vector pos, char **map, char *tex_id)
{
	t_dda	dda;
	int		flag;

	dda_init(&dda, ray, pos);
	while (!ft_strchr("123456789", map[dda.mapPoint.y][dda.mapPoint.x]))
	{
		if (dda.sideDistX < dda.sideDistY)
		{
			dda.sideDistX += dda.deltaDistX;
			dda.mapPoint.x += dda.stepX;
			flag = 0xF0;
		}
		else
		{
			dda.sideDistY += dda.deltaDistY;
			dda.mapPoint.y += dda.stepY;
			flag = 0x00;
		}
	}
	*tex_id = (map[dda.mapPoint.y][dda.mapPoint.x] - '0') | flag;
	if (flag == 0xF0)
		return ((dda.mapPoint.x - pos.x + (1 - dda.stepX) / 2) / ray.x);
	else
		return ((dda.mapPoint.y - pos.y + (1 - dda.stepY) / 2) / ray.y);
}

t_vector	get_tex_data(t_vector ray, t_vector pos,
			t_data *data, t_image **tex)
{
	t_vector	trash;
	float		dist;
	char		tex_id;

	dist = dda(ray, pos, data->map, &tex_id);
	if (tex_id & 0xF0)
	{
		tex_id &= ~0xF0;
		trash.x = pos.y + dist * ray.y;
		if (ray.x > 0)
			*tex = &data->textures[4 * (int)tex_id + 1];
		else
			*tex = &data->textures[4 * (int)tex_id + 3];
	}
	else
	{
		trash.x = pos.x + dist * ray.x;
		if (ray.y > 0)
			*tex = &data->textures[4 * (int)tex_id];
		else
			*tex = &data->textures[4 * (int)tex_id + 2];
	}
	trash.x -= floorf(trash.x);
	trash.y = dist;
	return (trash);
}
