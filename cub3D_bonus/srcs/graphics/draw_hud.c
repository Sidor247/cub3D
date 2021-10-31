/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:21:56 by cwhis             #+#    #+#             */
/*   Updated: 2021/10/31 17:28:52 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	put_scaled_pixel(t_image *img, t_point start, unsigned int color)
{
	t_point	tmp;
	t_point	pixel;

	if (color == 0x0000FFFF)
		return ;
	tmp.y = -1;
	while (++tmp.y < HUD_SCALE)
	{
		tmp.x = -1;
		while (++tmp.x < HUD_SCALE)
		{
			pixel = point(start.x + tmp.x, start.y + tmp.y);
			*get_pix_addr(img, pixel)= color;
			img->stencil_buf[pixel.y][pixel.x] = 1;
		}
	}
}

void	draw_element(t_image *img, t_image *element, t_point start)
{
	t_point	point1;
	t_point	point2;
	t_res	res;

	res = element->res;
	point1.y = -1;
	point2.y = start.y;
	while (++point1.y < res.height)
	{
		point1.x = -1;
		point2.x = start.x;
		while (++point1.x < res.width)
		{
			if (!img->stencil_buf[point2.y][point2.x])
				put_scaled_pixel(img, point2, *get_pix_addr(element, point1));
			point2.x += HUD_SCALE;
		}
		point2.y += HUD_SCALE;
	}
}

void	draw_number(t_image *img, t_image *dig, int n, t_point start)
{
	t_res	res;
	char	arr[3];
	int		i;

	ft_memcpy(arr, "   ", 3);
	if (n > 999)
		ft_memcpy(arr, "999", 3);
	else if (n < 1)
		ft_memcpy(arr, "  0", 3);
	else
	{
		i = 2;
		while (n)
		{
			arr[i] = n % 10 + '0';
			n /= 10;
			i--;
		}
	}
	res = dig[0].res;
	i = -1;
	while (++i < 3)
		if (arr[i] != ' ')
			draw_element(img, &dig[(int)(arr[i] - '0')],
				point(start.x + HUD_SCALE * i * res.width, start.y));
}

void	draw_ammo(t_image *img, t_image *dig, int *ammo, t_point start)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		draw_number(img, dig, ammo[i], start);
		start.y += 12 * HUD_SCALE;
	}
}

void	draw_hud(t_image *img, t_data *data)
{
	t_res	res;
	t_point	hud;
	t_stats	*stats;

	res = img->res;
	stats = &data->stats;
	hud = point(res.width / 2 - HUD_SCALE * 158, res.height - HUD_SCALE * 28);
	if (stats->c_weapon == -1)
		draw_number(img, data->hud.big, -1, hud);
	else
		draw_number(img, data->hud.big, stats->ammo[stats->c_weapon], hud);
	hud.x += 46 * HUD_SCALE;
	draw_number(img, data->hud.big, stats->health, hud);
	hud.x += 42 * HUD_SCALE;
	draw_element(img, &data->hud.big[10], hud);
	hud.x += 88 * HUD_SCALE;
	draw_number(img, data->hud.big, stats->armor, hud);
	hud.x += 40 * HUD_SCALE;
	draw_element(img, &data->hud.big[10], hud);
	hud = point(hud.x + 58 * HUD_SCALE, hud.y + HUD_SCALE);
	draw_ammo(img, data->hud.med_l, stats->ammo, hud);
	hud.x += 25 * HUD_SCALE;
	draw_ammo(img, data->hud.med_l, stats->max_ammo, hud);
	hud = point((res.width - HUD_SCALE * 320) / 2, res.height - HUD_SCALE * 32);
	draw_element(img, &data->hud.back, hud);
}
