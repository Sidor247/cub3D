/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:54:42 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/17 19:04:46 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	push_front(t_sprites *sprites, float x, float y)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (sprite == NULL)
		return (1);
	sprite->pos.x = x;
	sprite->pos.y = y;
	sprite->prev = NULL;
	sprite->next = sprites->start;
	if (sprites->end == NULL)
		sprites->end = sprite;
	else
		sprites->start->prev = sprite;
	sprites->start = sprite;
	return (0);
}

int	sprites_init(t_sprites *sprites, char **map)
{
	int	i;
	int	j;
	int	flag;

	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (map[j][i] == '2')
			{
				flag = push_front(sprites, i + 0.5, j + 0.5);
				if (flag)
					return (1);
			}
		}
	}
	return (0);
}

void	draw_init(t_sdraw *sdraw, t_data *data, t_vector transform)
{
	sdraw->spriteScreenX = (int)((data->res.width / 2)
			* (1 + transform.x / transform.y));
	sdraw->size = abs((int)(data->res.height / transform.y));
	if (-sdraw->size / 2 + sdraw->spriteScreenX < 0)
		sdraw->draw_start.x = 0;
	else
		sdraw->draw_start.x = -sdraw->size / 2 + sdraw->spriteScreenX;
	if ((-sdraw->size + data->res.height) / 2 < 0)
		sdraw->draw_start.y = 0;
	else
		sdraw->draw_start.y = (-sdraw->size + data->res.height) / 2;
	if (sdraw->size / 2 + sdraw->spriteScreenX > data->res.width)
		sdraw->draw_end.x = data->res.width;
	else
		sdraw->draw_end.x = sdraw->size / 2 + sdraw->spriteScreenX;
	if ((sdraw->size + data->res.height) / 2 > data->res.height)
		sdraw->draw_end.y = data->res.height;
	else
		sdraw->draw_end.y = (sdraw->size + data->res.height) / 2;
}

void	draw_sprite(t_image *img, t_data *data, t_vector transform)
{
	t_sdraw	sdraw;
	t_point	point;
	t_image	*tex;

	draw_init(&sdraw, data, transform);
	point.x = sdraw.draw_start.x - 1;
	tex = &data->textures[4];
	while (++point.x < sdraw.draw_end.x)
	{
		if (transform.y > 0 && transform.y < data->dist_buf[point.x])
		{
			sdraw.tex.x = (int)(256
					* (point.x - (-sdraw.size / 2 + sdraw.spriteScreenX))
					* data->textures[4].res.width / sdraw.size) / 256;
			point.y = sdraw.draw_start.y - 1;
			while (++point.y < sdraw.draw_end.y)
			{
				sdraw.tex.y = (point.y * 256 + (sdraw.size - data->res.height)
						* 128) * tex->res.height / sdraw.size / 256;
				if (*get_pix_addr(tex, sdraw.tex.x, sdraw.tex.y) != 0xFF000000)
					*get_pix_addr(img, point.x, point.y)
					= *get_pix_addr(tex, sdraw.tex.x, sdraw.tex.y);
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
	float		det;

	tmp = data->sprites.start;
	player = data->player;
	det = 1.0 / (player.plane.x * player.dir.y
			- player.dir.x * player.plane.y);
	while (tmp)
	{
		sprite.x = tmp->pos.x - player.pos.x;
		sprite.y = tmp->pos.y - player.pos.y;
		transform.x = det
			* (player.dir.y * sprite.x - player.dir.x * sprite.y);
		transform.y = det
			* (-player.plane.y * sprite.x + player.plane.x * sprite.y);
		draw_sprite(img, data, transform);
		tmp = tmp->next;
	}
}
