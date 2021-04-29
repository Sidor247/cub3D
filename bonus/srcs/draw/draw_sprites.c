/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 00:48:49 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/26 02:51:20 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_init(t_sdraw *sdraw, t_res res, t_vector transform)
{
	int	spriteScreenX;

	spriteScreenX = (int)((res.width / 2) * (1 + transform.x / transform.y));
	sdraw->size = abs((int)(res.height / transform.y));
	sdraw->c_draw_start.x = -sdraw->size / 2 + spriteScreenX;
	sdraw->c_draw_start.y = (-sdraw->size + res.height) / 2;
	sdraw->c_draw_end.x = sdraw->size / 2 + spriteScreenX;
	sdraw->c_draw_end.y = (sdraw->size + res.height) / 2;
	if (sdraw->c_draw_start.x < 0)
		sdraw->draw_start.x = 0;
	else
		sdraw->draw_start.x = sdraw->c_draw_start.x;
	if (sdraw->c_draw_start.y < 0)
		sdraw->draw_start.y = 0;
	else
		sdraw->draw_start.y = sdraw->c_draw_start.y;
	if (sdraw->c_draw_end.x > res.width)
		sdraw->draw_end.x = res.width;
	else
		sdraw->draw_end.x = sdraw->c_draw_end.x;
	if (sdraw->c_draw_end.y > res.height)
		sdraw->draw_end.y = res.height;
	else
		sdraw->draw_end.y = sdraw->c_draw_end.y;
}

void	draw_sprite(t_image *img, t_image *tex,
		float *dist_buf, t_vector transform)
{
	t_sdraw			sdraw;
	t_point			point;
	t_point			tex_point;
	unsigned int	color;

	draw_init(&sdraw, img->res, transform);
	point.x = sdraw.draw_start.x - 1;
	while (++point.x < sdraw.draw_end.x)
	{
		if (transform.y > 0 && transform.y < dist_buf[point.x])
		{
			tex_point.x = (int)(256 * (point.x - sdraw.c_draw_start.x)
					* tex->res.width / sdraw.size) / 256;
			point.y = sdraw.draw_start.y - 1;
			while (++point.y < sdraw.draw_end.y)
			{
				tex_point.y = (point.y - sdraw.c_draw_start.y) * 256
					* tex->res.height / sdraw.size / 256;
				color = *get_pix_addr(tex, tex_point);
				if (color != 0xFF000000)
					*get_pix_addr(img, point) = color;
			}
		}
	}
}

void	draw_sprites(t_image *img, t_data *data)
{
	t_sprite	*tmp;
	t_player	player;
	t_vector	transform;
	t_vector	sprite;
	t_vector	plane;

	tmp = data->sprites.start;
	player = data->player;
	plane = get_plane(player.dir);
	while (tmp)
	{
		sprite.x = tmp->pos.x - player.pos.x;
		sprite.y = tmp->pos.y - player.pos.y;
		sprite = sub_vec(tmp->pos, player.pos);
		transform.x = player.dir.y * sprite.x - player.dir.x * sprite.y;
		transform.y = -plane.y * sprite.x + plane.x * sprite.y;
		transform = mult_vec(1.0 / (plane.x * player.dir.y
					- player.dir.x * plane.y), transform);
		draw_sprite(img, tmp->tex, data->dist_buf, transform);
		tmp = tmp->next;
	}
}
