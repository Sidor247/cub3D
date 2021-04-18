/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:51:43 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/17 19:04:21 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_moves(t_player *player, int keys)
{
	player->move = 0;
	player->strafe = 0;
	player->rotate = 0;
	player->run = 1;
	if (keys & 0x01)
		player->move++;
	if (keys & 0x02)
		player->move--;
	if (keys & 0x04)
		player->strafe++;
	if (keys & 0x08)
		player->strafe--;
	if (keys & 0x10)
		player->rotate++;
	if (keys & 0x20)
		player->rotate--;
	if (keys & 0x40 || keys & 0x80)
		player->run++;
}

int	key_press(int key, int *keys)
{
	if (key == W)
		*keys |= 0x01;
	else if (key == S)
		*keys |= 0x02;
	else if (key == D)
		*keys |= 0x04;
	else if (key == A)
		*keys |= 0x08;
	else if (key == RIGHT)
		*keys |= 0x10;
	else if (key == LEFT)
		*keys |= 0x20;
	else if (key == L_SHIFT)
		*keys |= 0x40;
	else if (key == R_SHIFT)
		*keys |= 0x80;
	else if (key == ESC)
		*keys |= 0x8000;
	return (1);
}

int	key_release(int key, int *keys)
{
	if (key == W)
		*keys &= ~0x01;
	else if (key == S)
		*keys &= ~0x02;
	else if (key == D)
		*keys &= ~0x04;
	else if (key == A)
		*keys &= ~0x08;
	else if (key == RIGHT)
		*keys &= ~0x10;
	else if (key == LEFT)
		*keys &= ~0x20;
	else if (key == L_SHIFT)
		*keys &= ~0x40;
	else if (key == R_SHIFT)
		*keys &= ~0x80;
	return (1);
}
