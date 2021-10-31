/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rocket_launcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 19:41:30 by cwhis             #+#    #+#             */
/*   Updated: 2021/10/31 01:12:43 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	projectile(t_data *data)
{
	t_player	*player;
	t_sprite	*tmp_sp;
	t_vector	tmp_vec;
	float		dist;

	player = &data->player;
	tmp_sp = data->sprites.end;
	dist = data->z_buf[data->res.width / 2];
	while (tmp_sp)
	{
		if (ft_strchr("ABCD", tmp_sp->id))
		{
			tmp_vec = sub_vec(tmp_sp->pos, player->pos);
			if (hypotf(tmp_vec.x, tmp_vec.y) > dist)
				break ;
			if (fabsf(tmp_vec.x * player->dir.y - tmp_vec.y * player->dir.x)
				< OBJ_COL 
				&& tmp_vec.x * player->dir.x + tmp_vec.y * player->dir.y > 0)
			{
				dist = hypotf(tmp_vec.x, tmp_vec.y);
				break ;
			}
		}
		tmp_sp = tmp_sp->prev;
	}
	init_blow(data, add_vec(player->pos, mult_vec(dist - 0.1, player->dir)),
		(int)dist * CLOCKS_PER_SEC / R_SPEED);
}

void	rocket_launcher(t_data *data)
{
	int			*frame;
	int			time_diff;

	frame = &data->weapons[1].frame;
	time_diff = (int)(data->timer - data->time);
	if (*frame == 0)
	{
		*frame = 1;
		data->stats.ammo[1]--;
		projectile(data);
		system(RL_SOUND);
	}
	else if (*frame == 1 && time_diff < CLOCKS_PER_SEC / 10 * 3)
		*frame = 2;
	else if (*frame == 2 && time_diff < CLOCKS_PER_SEC / 10 * 2)
		*frame = 3;
	else if (*frame == 3 && time_diff < CLOCKS_PER_SEC / 10 * 1)
		*frame = 4;
	else if (*frame == 4 && time_diff < 0)
	{
		*frame = 0;
		data->timer = 0;
	}
}