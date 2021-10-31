/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 22:42:48 by cwhis             #+#    #+#             */
/*   Updated: 2021/10/30 23:11:10 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	shoot_request(t_data *data)
{
	int	c_weapon;

	c_weapon = data->stats.c_weapon;
	if (data->timer || data->stats.ammo[c_weapon] < 1)
		return ;
	if (c_weapon == 0)
		data->timer = data->time + CLOCKS_PER_SEC / 4;
	else if (c_weapon == 1)
		data->timer = data->time + CLOCKS_PER_SEC / 2;
}

void	shoot(t_data *data)
{
	int	c_weapon;

	c_weapon = data->stats.c_weapon;
	if (c_weapon == 0)
		chaingun(data);
	else if (c_weapon == 1)
		rocket_launcher(data);
}
