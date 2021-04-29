/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 22:42:48 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/28 17:25:16 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	shoot_request(t_data *data)
{
	int	c_weapon;

	c_weapon = data->stats.c_weapon;
	if (data->timer || data->stats.ammo[c_weapon] < 1)
		return ;
	if (c_weapon == 0)
		data->timer = data->time + CLOCKS_PER_SEC / 5;
	else if (c_weapon == 1)
		data->timer = data->time + CLOCKS_PER_SEC / 2;
}

void	shoot(t_mlx *mlx)
{
	int	c_weapon;

	c_weapon = mlx->data.stats.c_weapon;
	if (c_weapon == 0)
		chaingun(mlx);
	else if (c_weapon == 1)
		rocket_launcher(mlx);
}

void	hit_scan(t_data *data)
{
	t_player	*player;
	t_sprite	*tmp_sp;
	t_vector	tmp_vec;
	float		dist;

	player = &data->player;
	tmp_sp = data->sprites.end;
	dist = data->dist_buf[data->res.width / 2];
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
	init_bullet(data, add_vec(player->pos, mult_vec(dist - 0.05, player->dir)));
}

void	chaingun(t_mlx *mlx)
{
	int		*frame;
	int		time_diff;

	frame = &mlx->data.weapons[0].frame;
	time_diff = (int)(mlx->data.timer - mlx->data.time);
	if (*frame == 0)
	{
		*frame = 1;
		mlx->data.stats.ammo[0]--;
		hit_scan(&mlx->data);
		play_sound(mlx, CG_SOUND);
	}
	else if (*frame == 1 && time_diff < CLOCKS_PER_SEC / 10)
	{
		*frame = 2;
		mlx->data.stats.ammo[0]--;
		hit_scan(&mlx->data);
		play_sound(mlx, CG_SOUND);
	}
	else if (*frame == 2 && time_diff < 0)
	{
		*frame = 0;
		mlx->data.timer = 0;
	}
}

void	rocket_launcher(t_mlx *mlx)
{
	int	*frame;
	int	time_diff;

	frame = &mlx->data.weapons[1].frame;
	time_diff = (int)(mlx->data.timer - mlx->data.time);
	if (*frame == 0)
	{
		*frame = 1;
		mlx->data.stats.ammo[1]--;
		play_sound(mlx, RL_SOUND);
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
		mlx->data.timer = 0;
	}
}
