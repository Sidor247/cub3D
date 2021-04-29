/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:06:14 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/27 23:48:50 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	wall_collisions(t_vector pos, t_vector *delta, char **map)
{
	if (delta->x > 0 && ft_strchr("123456789",
			map[(int)(pos.y + delta->y)][(int)(pos.x + delta->x + PLR_COL)]))
		delta->x = ceilf(pos.x) - PLR_COL - pos.x;
	else if (delta->x < 0 && ft_strchr("123456789",
			map[(int)(pos.y + delta->y)][(int)(pos.x + delta->x - PLR_COL)]))
		delta->x = floorf(pos.x) + PLR_COL - pos.x;
	if (delta->y > 0 && ft_strchr("123456789",
			map[(int)(pos.y + delta->y + PLR_COL)][(int)(pos.x + delta->x)]))
		delta->y = ceilf(pos.y) - PLR_COL - pos.y;
	else if (delta->y < 0 && ft_strchr("123456789",
			map[(int)(pos.y + delta->y - PLR_COL)][(int)(pos.x + delta->x)]))
		delta->y = floorf(pos.y) + PLR_COL - pos.y;
}

void	obj_collisions(t_vector pos, t_vector *delta, t_mlx *mlx)
{
	t_sprite	*tmp;

	tmp = mlx->data.sprites.end;
	while (tmp && hypotf(tmp->pos.x - (pos.x + delta->x),
			tmp->pos.y - (pos.y + delta->y)) < 1)
	{
		if (ft_strchr("ABCD" , tmp->id))
		{
			if (delta->x > 0 && fabsf(tmp->pos.y - (pos.y + delta->y)) < OBJ_COL
				&& fabsf(tmp->pos.x - (pos.x + delta->x + PLR_COL)) < OBJ_COL)
				delta->x = tmp->pos.x - OBJ_COL - PLR_COL - pos.x;
			if (delta->x < 0 && fabsf(tmp->pos.y - (pos.y + delta->y)) < OBJ_COL
				&& fabsf(tmp->pos.x - (pos.x + delta->x - PLR_COL)) < OBJ_COL)
				delta->x = tmp->pos.x + OBJ_COL + PLR_COL - pos.x;
			if (delta->y > 0 && fabsf(tmp->pos.x - (pos.x + delta->x)) < OBJ_COL
				&& fabsf(tmp->pos.y - (pos.y + delta->y + PLR_COL)) < OBJ_COL)
				delta->y = tmp->pos.y - OBJ_COL - PLR_COL - pos.y;
			if (delta->y < 0 && fabsf(tmp->pos.x - (pos.x + delta->x)) < OBJ_COL
				&& fabsf(tmp->pos.y - (pos.y + delta->y - PLR_COL)) < OBJ_COL)
				delta->y = tmp->pos.y + OBJ_COL + PLR_COL - pos.y;
		}
		else if (ft_strchr("abcdef", tmp->id))
			pick(mlx, tmp);
		tmp = tmp->prev;
	}
}