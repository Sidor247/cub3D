/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:51:25 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/25 23:23:45 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

void	put_tex_stripe(t_image *img, int x, t_vector trash, t_image *tex)
{
	t_point		tex_point;
	t_point		point;
	float		step;
	float		tex_pos;
	int			finish;

	step = (float)tex->res.height / trash.y;
	point.x = x;
	point.y = (img->res.height - (int)trash.y) / 2;
	if (point.y < 0)
		point.y = 0;
	finish = img->res.height - point.y;
	tex_point.x = (int)((float)tex->res.width * trash.x);
	tex_pos = (point.y + ((int)trash.y - img->res.height) / 2) * step;
	while (point.y < finish)
	{
		tex_point.y = (int)tex_pos & (tex->res.height - 1);
		*get_pix_addr(img, point) = *get_pix_addr(tex, tex_point);
		tex_pos += step;
		point.y++;
	}
}

void	draw_ceil(t_image *img, unsigned int color)
{
	t_point	tmp;
	t_res	res;
	int		half;

	res = img->res;
	half = res.height / 2;
	tmp.y = 0;
	while (tmp.y < half)
	{
		tmp.x = 0;
		while (tmp.x < res.width)
		{
			*get_pix_addr(img, tmp) = color;
			tmp.x++;
		}
		tmp.y++;
	}
}

void	draw_tex_floor(t_image *img, t_vector dir, t_vector pos, t_image *tex)
{
	t_vector	floor_step;
	t_vector	floor;
	t_point		point;
	t_point		tex_point;
	float		row_dist;

	point.y = img->res.height / 2;
	while (++point.y < img->res.height)
	{
		row_dist = img->res.height / (2.0 * (point.y - img->res.height / 2));
		floor_step = mult_vec(2 * row_dist / img->res.width, get_plane(dir));
		floor = add_vec(pos, mult_vec(row_dist, sub_vec(dir, get_plane(dir))));
		point.x = -1;
		while (++point.x < img->res.width)
		{
			tex_point.x = (int)(tex->res.width * (floor.x - floorf(floor.x)));
			tex_point.y = (int)(tex->res.height * (floor.y - floorf(floor.y)));
			if (tex_point.x >= img->res.width)
				tex_point.x = img->res.width - 1;
			if (tex_point.y >= img->res.height)
				tex_point.y = img->res.height - 1;
			*get_pix_addr(img, point) = *get_pix_addr(tex, tex_point);
			floor = add_vec(floor, floor_step);
		}
	}
}

void	draw_walls(t_image *img, t_player *player, t_data *data)
{
	t_vector	ray;
	t_vector	trash;
	t_image		*tex;
	float		tmp;
	int			x;

	x = 0;
	while (x < data->res.width)
	{
		tmp = 2 * (float)x / (float)data->res.width - 1;
		ray = add_vec(player->dir, mult_vec(tmp, get_plane(player->dir)));
		trash = get_tex_data(ray, player->pos, data, &tex);
		data->dist_buf[x] = trash.y;
		trash.y = (float)data->res.height / trash.y;
		put_tex_stripe(img, x, trash, tex);
		x++;
	}
}
