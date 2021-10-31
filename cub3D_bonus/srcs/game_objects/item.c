/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 00:46:56 by cwhis             #+#    #+#             */
/*   Updated: 2021/10/30 02:28:31 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	pick_item(int *item, int n, int max)
{
	if (*item == max)
		return (0);
	*item += n;
	if (*item > max)
		*item = max;
	return (1);
}

int	pick_weapon(t_stats *stats, char id)
{
	int	flag;

	flag = 0;
	if (id == 'd')
	{
		if (!(stats->weapons & 0x01))
		{
			flag++;
			stats->weapons |= 0x01;
			stats->c_weapon = 0;
		}
		flag += pick_item(&stats->ammo[0], 30, stats->max_ammo[0]);
	}
	if (id == 'e')
	{
		if (!(stats->weapons & 0x02))
		{
			flag++;
			stats->weapons |= 0x02;
			stats->c_weapon = 1;
		}
		flag += pick_item(&stats->ammo[1], 5, stats->max_ammo[1]);
	}
	return (flag);
}

void	pick(t_mlx *mlx, t_sprite *sprite)
{
	t_stats 	*stats;
	int			flag;

	flag = 0;
	stats = &mlx->data.stats;
	if (sprite->id == 'a')
		flag = pick_item(&stats->ammo[0], 50, stats->max_ammo[0]);		
	else if (sprite->id == 'b')
		flag = pick_item(&stats->armor, 50, 100);
	else if (sprite->id == 'c')
		flag = pick_item(&stats->health, 30, 100);
	else if (sprite->id == 'd')
		flag = pick_weapon(stats, 'd');
	else if (sprite->id == 'e')
		flag = pick_weapon(stats, 'e');
	else if (sprite->id == 'f')
		flag = pick_item(&stats->ammo[1], 10, stats->max_ammo[1]);
	if (flag)
	{
		system(PICKUP_SOUND);
		delete_sprite(&mlx->data.sprites, sprite);
	}
}