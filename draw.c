/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 19:41:31 by cwhis             #+#    #+#             */
/*   Updated: 2021/02/28 19:50:56 by cwhis            ###   ########.fr       */
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
		while(i < size / 2)
		{
			dst = img->addr + (center.y + j) * img->line_length +
			(center.x + i) * (img->bits_per_pixel / 8);
			*(unsigned int*)dst = color;
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
	length = sqrtf(line.x * line.x + line.y * line.y);
	sin_a = line.x / length;
	cos_a = line.y / length;
	while (i < length)
	{
		dst = img->addr + (y + (int)((float)i * sin_a)) * img->line_length +
		(x + (int)((float)i * cos_a)) * (img->bits_per_pixel / 8);
		*(unsigned int*)dst = color;
		i++;
	}
}

void	draw_map(t_image *img, char **map)
{
	int	i = 0;
	int	j = 0;
	int x = 20;
	int y = 20;

	while (map[j])
	{
		while (map[j][i])
		{
			if (map[j][i] == '1')
				put_square(img, x, y, 20, BLUE);
			else
				put_square(img, x, y, 20, BLACK);
			i++;
			x += 20;
		}
		i = 0;
		x = 20;
		j++;
		y += 20;
	}
}

void	draw_player(t_image *img, t_player *player)
{
	put_square(img, 20 + (int)(player->x * 20),
	20 + (int)(player->y * 20), (int)(20 * COL_SIZE), GREEN);
	put_line(img, 20 + (int)(player->x * 20),
	20 + (int)(player->y * 20), 50, player->dir, RED);
}
