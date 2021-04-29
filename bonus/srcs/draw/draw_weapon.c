/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:43:33 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/27 14:05:18 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_weapon(t_image *img, t_data *data)
{
	t_image		*tex;
	int			c_weapon;

	c_weapon = data->stats.c_weapon;
	if (c_weapon == -1)
		return ;
	tex = &data->weapons[c_weapon].tex[data->weapons[c_weapon].frame];
	draw_element(img, tex,
		point((img->res.width - tex->res.width * HUD_SCALE) / 2,
				img->res.height - tex->res.height * HUD_SCALE));
}
