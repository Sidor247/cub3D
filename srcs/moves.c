/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:53:56 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/17 19:04:34 by cwhis            ###   ########.fr       */
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

void	collision_check(t_vector *pos, t_vector delta, char **map)
{
	float	x;
	float	y;

	x = pos->x;
	y = pos->y;
	if (delta.x > 0
		&& map[(int)(y + delta.y)][(int)(x + delta.x + COL_SIZE)] == '1')
		x = ceilf(x) - COL_SIZE;
	else if (delta.x < 0
		&& map[(int)(y + delta.y)][(int)(x + delta.x - COL_SIZE)] == '1')
		x = floorf(x) + COL_SIZE;
	else
		x += delta.x;
	if (delta.y > 0
		&& map[(int)(y + delta.y + COL_SIZE)][(int)(x + delta.x)] == '1')
		y = ceilf(y) - COL_SIZE;
	else if (delta.y < 0
		&& map[(int)(y + delta.y - COL_SIZE)][(int)(x + delta.x)] == '1')
		y = floorf(y) + COL_SIZE;
	else
		y += delta.y;
	pos->x = x;
	pos->y = y;
}

void	move_player(t_player *player, char **map)
{
	t_vector	delta;

	if (player->move || player->strafe)
	{
		delta.x = ((float)(player->move) *player->dir.x
				+ (float)(player->strafe) *(-player->dir.y))
			* SPEED * player->run;
		delta.y = ((float)(player->move) *player->dir.y
				+ (float)(player->strafe) *player->dir.x)
			* SPEED * player->run;
		collision_check(&player->pos, delta, map);
	}
	if (player->rotate)
	{
		rotate_player(&player->dir, (float)player->rotate * ROT);
		update_plane(player);
	}
}
