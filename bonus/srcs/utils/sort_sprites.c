/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:54:11 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/25 23:24:15 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	sprite_cmp(t_vector a, t_vector b, t_vector pos)
{
	t_vector	v1;
	t_vector	v2;

	v1.x = pos.x - a.x;
	v1.y = pos.y - a.y;
	v2.x = pos.x - b.x;
	v2.y = pos.y - b.y;
	return (v1.x * v1.x + v1.y * v1.y < v2.x * v2.x + v2.y * v2.y);
}

void	swap_sprites(t_sprites *sprites, t_sprite *a)
{
	t_sprite	*b;

	b = a->next;
	if (sprites->start == a)
		sprites->start = b;
	else
		a->prev->next = b;
	if (sprites->end == b)
		sprites->end = a;
	else
		b->next->prev = a;
	a->next = b->next;
	b->prev = a->prev;
	a->prev = b;
	b->next = a;
}	

void	sort_sprites(t_sprites *sprites, t_vector pos)
{
	t_sprite	*tmp;
	t_sprite	*last;
	t_sprite	*swaped;

	last = NULL;
	swaped = sprites->start;
	while (swaped)
	{
		swaped = NULL;
		tmp = sprites->start;
		while (tmp->next != last)
		{
			if (sprite_cmp(tmp->pos, tmp->next->pos, pos))
			{
				swap_sprites(sprites, tmp);
				swaped = tmp;
			}
			else
				tmp = tmp->next;
		}
		last = swaped;
	}
}
