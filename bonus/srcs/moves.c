/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:53:56 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/27 23:10:46 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_player(t_vector *dir, float a)
{
	float	length;
	float	x;
	float	y;

	x = dir->x;
	y = dir->y;
	x = x * cosf(a) - y * sinf(a);
	y = x * sinf(a) + y * cosf(a);
	length = hypotf(x, y);
	dir->x = x / length;
	dir->y = y / length;
}

void	move_player(t_mlx *mlx)
{
	t_vector	delta;
	t_player	*player;
	char		**map;	

	player = &mlx->data.player;
	map = mlx->data.map;
	if (player->move || player->strafe)
	{
		delta.x = ((float)(player->move) *player->dir.x
				+ (float)(player->strafe) *(-player->dir.y))
			* SPEED * player->run;
		delta.y = ((float)(player->move) *player->dir.y
				+ (float)(player->strafe) *player->dir.x)
			* SPEED * player->run;
		wall_collisions(player->pos, &delta, map);
		obj_collisions(player->pos, &delta, mlx);
		player->pos.x += delta.x;
		player->pos.y += delta.y;
	}
	if (player->rotate)
		rotate_player(&player->dir, (float)player->rotate * ROT);
}

void	mouse_rotation(t_mlx *mlx)
{
	t_point	pos;
	t_res	res;
	int		x;

	res = mlx->data.res;
	mlx_mouse_get_pos(mlx->win, &pos.x, &pos.y);
	mlx_mouse_move(mlx->win, res.width / 2, res.height / 2);
	x = pos.x - res.width / 2;
	if (x)
		rotate_player(&mlx->data.player.dir, (float)x * SENS);
}
