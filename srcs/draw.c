/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:51:25 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/17 19:04:14 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	float		step;
	float		tex_pos;
	int			start;
	int			finish;

	step = (float)tex->res.height / trash.y;
	start = (img->res.height - (int)trash.y) / 2;
	if (start < 0)
		start = 0;
	finish = img->res.height - start;
	tex_point.x = (int)((float)tex->res.width * trash.x);
	tex_pos = (start + ((int)trash.y - img->res.height) / 2) * step;
	while (start < finish)
	{
		tex_point.y = (int)tex_pos & (tex->res.height - 1);
		*get_pix_addr(img, x, start)
		= *get_pix_addr(tex, tex_point.x, tex_point.y);
		tex_pos += step;
		start++;
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
			*get_pix_addr(img, tmp.x, tmp.y) = color;
			tmp.x++;
		}
		tmp.y++;
	}
}

void	draw_floor(t_image *img, unsigned int color)
{
	t_point	tmp;
	t_res	res;
	int		half;

	res = img->res;
	half = res.height / 2;
	tmp.y = half;
	while (tmp.y < res.height)
	{
		tmp.x = 0;
		while (tmp.x < res.width)
		{
			*get_pix_addr(img, tmp.x, tmp.y) = color;
			tmp.x++;
		}
		tmp.y++;
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
		ray.x = player->dir.x + player->plane.x * tmp;
		ray.y = player->dir.y + player->plane.y * tmp;
		trash = get_tex_data(ray, player->pos, data, &tex);
		data->dist_buf[x] = trash.y;
		trash.y = (float)data->res.height / trash.y;
		put_tex_stripe(img, x, trash, tex);
		x++;
	}
}
