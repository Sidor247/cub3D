/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:00:09 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/28 17:09:54 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_bullet(t_data *data, t_vector pos)
{
	t_effect	*effect;

	effect = malloc(sizeof(effect));
	effect->sprite = push_front(&data->sprites, pos, '*', &data->bullet[0]);
	effect->arr = data->bullet;
	effect->frame = 0;
	effect->id = 'b';
	effect->timer = data->time + CLOCKS_PER_SEC / 2;
	ft_lstadd_front(&data->effects, ft_lstnew(effect));
}

void	bullet_effect(t_effect *effect, clock_t time)
{
	int			time_diff;

	time_diff = (int)(effect->timer - time);
	if (effect->frame == 0 && time_diff < CLOCKS_PER_SEC * 3 / 8)
	{
		effect->frame = 1;
		effect->sprite->tex = &effect->arr[1];
	}
	else if (effect->frame == 1 && time_diff < CLOCKS_PER_SEC * 4)
	{
		effect->frame = 2;
		effect->sprite->tex = &effect->arr[2];
	}
	else if (effect->frame == 2 && time_diff < CLOCKS_PER_SEC / 8)
	{
		effect->frame = 3;
		effect->sprite->tex = &effect->arr[3];
	}
	else if (effect->frame == 3 && time_diff < 0)
		effect->frame = -1;
}

void	show_effects(t_data *data)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*prev;
	
	tmp = data->effects;
	prev = NULL;
	while (tmp)
	{
		if (((t_effect *)tmp->content)->id == 'b')
			bullet_effect(tmp->content, data->time);
		if (((t_effect *)tmp->content)->frame == -1)
		{
			delete_sprite(&data->sprites, ((t_effect *)tmp->content)->sprite);
			if (prev)
				prev->next = tmp->next;
			else
				data->effects = tmp->next;
			tmp2 = tmp->next;
			ft_lstdelone(tmp, free);
			tmp = tmp2;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
