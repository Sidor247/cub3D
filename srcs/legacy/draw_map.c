/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:55:01 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/13 15:43:37 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_square(t_image *img, t_point center, int size, int color)
{
	char	*dst;
	int		i;
	int		j;

	i = -(size / 2);
	j = -(size / 2);
	while (j < size / 2)
	{
		while (i < size / 2)
		{
			dst = img->addr + (center.y + j) * img->line_length
				+ (center.x + i) * (img->bits_per_pixel / 8);
			*(unsigned int *)dst = color;
			i++;
		}
		i = -(size / 2);
		j++;
	}
}

void	put_line(t_image *img, t_point point, t_vector line, int color)
{
	float	sin_a;
	float	cos_a;
	float	length;
	char	*dst;
	int		i;

	i = 0;
	length = hypotf(line.x, line.y);
	sin_a = line.x / length;
	cos_a = line.y / length;
	while (i < (int)length)
	{
		dst = img->addr + (point.y + (int)((float)i * cos_a)) * img->line_length
			+ (point.x + (int)((float)i * sin_a)) * (img->bits_per_pixel / 8);
		*(unsigned int *)dst = color;
		i++;
	}
}

void	draw_map(t_image *img, char **map)
{
	t_point	point;
	int		i;
	int		j;

	point.x = 20;
	point.y = 20;
	i = 0;
	j = 0;
	while (map[j])
	{
		while (map[j][i])
		{
			if (map[j][i] == '1')
				put_square(img, point, 20, BLUE);
			else
				put_square(img, point, 20, BLACK);
			i++;
			point.x += 20;
		}
		i = 0;
		point.x = 20;
		j++;
		point.y += 20;
	}
}

void	draw_player(t_image *img, t_player *player, char **map)
{
	t_point		pos;
	float		dist;
	t_vector	ray;

	pos.x = (int)(20 * player->pos.x + 10);
	pos.y = (int)(20 * player->pos.y + 10);
	dist = mini_dda(player->dir, player->pos, map);
	ray.x = 20 * dist * player->dir.x;
	ray.y = 20 * dist * player->dir.y;
	put_square(img, pos, (int)(20 * COL_SIZE * 2), GREEN);
	put_line(img, pos, ray, RED);
}

void	draw_rays(t_image *img, t_player *player, char **map)
{
	t_vector	ray;
	t_point		map_pos;
	t_vector	plane;
	t_vector	trash;
	int			x;

	x = -1;
	plane.x = -(player->dir.y) * tanf(FOV * M_PI / 360);
	plane.y = player->dir.x * tanf(FOV * M_PI / 360);
	map_pos.x = (int)(20 * player->pos.x + 10);
	map_pos.y = (int)(20 * player->pos.y + 10);
	while (++x < 800)
	{
		trash.x = 2 * (float)x / 800.0 - 1;
		ray.x = player->dir.x + plane.x * trash.x;
		ray.y = player->dir.y + plane.y * trash.x;
		trash.y = hypotf(ray.x, ray.y);
		ray.x /= trash.y;
		ray.y /= trash.y;
		trash.y = dda(ray, player->pos, map, NULL);
		ray.x *= trash.y * 20;
		ray.y *= trash.y * 20;
		put_line(img, map_pos, ray, 0x00FFFFFF);
	}
}
