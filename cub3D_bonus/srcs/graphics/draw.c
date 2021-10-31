/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:51:25 by cwhis             #+#    #+#             */
/*   Updated: 2021/05/02 16:22:22 by cwhis            ###   ########.fr       */
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

void	put_tex_stripe(t_image *img, int x, float height, t_tex_data tex_data)
{
	t_point		tex_point;
	t_point		point;
	float		step;
	float		tex_pos;
	int			finish;

	step = (float)tex_data.tex->res.height / height;
	point.x = x;
	point.y = (img->res.height - (int)height) / 2;
	if (point.y < 0)
		point.y = 0;
	finish = img->res.height - point.y;
	tex_point.x = (int)((float)tex_data.tex->res.width * tex_data.x);
	tex_pos = (point.y + ((int)height - img->res.height) / 2) * step;
	while (point.y < finish)
	{
		if (img->stencil_buf[point.y][point.x] == 0)
		{
			tex_point.y = (int)tex_pos & (tex_data.tex->res.height - 1);
			*get_pix_addr(img, point) = *get_pix_addr(tex_data.tex, tex_point);
			img->stencil_buf[point.y][point.x] = 1;
		}
		tex_pos += step;
		point.y++;
	}
}

void	draw_ceil(t_image *img, unsigned int color)
{
	t_point	tmp;
	t_res	res;
	char	**stencil_buf;
	int		half;

	res = img->res;
	half = res.height / 2;
	stencil_buf = img->stencil_buf;
	tmp.y = 0;
	while (tmp.y < half)
	{
		tmp.x = -1;
		while (++tmp.x < res.width)
		{
			if (stencil_buf[tmp.y][tmp.x])
				continue;
			*get_pix_addr(img, tmp) = color;
			stencil_buf[tmp.y][tmp.x] = 1;
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
			if (img->stencil_buf[point.y][point.x] == 0)
			{
				tex_point.x = (int)(tex->res.width * (floor.x - floorf(floor.x)));
				tex_point.y = (int)(tex->res.height * (floor.y - floorf(floor.y)));
				if (tex_point.x >= img->res.width)
					tex_point.x = img->res.width - 1;
				if (tex_point.y >= img->res.height)
					tex_point.y = img->res.height - 1;
				*get_pix_addr(img, point) = *get_pix_addr(tex, tex_point);
				img->stencil_buf[point.y][point.x] = 1;
			}
			floor = add_vec(floor, floor_step);
		}
	}
}

void	draw_walls(t_image *img, t_data *data)
{
	t_tex_data	*tex_data;
	float		*z_buf;
	t_res		res;	
	int			x;

	x = -1;
	res = img->res;
	tex_data = data->tex_data;
	z_buf = data->z_buf;
	while (++x < res.width)
		put_tex_stripe(img, x, res.height / z_buf[x], tex_data[x]);
}
