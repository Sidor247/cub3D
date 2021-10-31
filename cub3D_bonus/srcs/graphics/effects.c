/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:00:09 by cwhis             #+#    #+#             */
/*   Updated: 2021/10/31 11:23:28 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_bullet(t_data *data, t_vector pos)
{
	t_eff_list	*effect;

	effect = malloc(sizeof(t_eff_list));
	effect->sprite = push_front(&data->sprites, pos, '*', &data->bullet[0]);
	effect->arr = data->bullet;
	effect->frame = 0;
	effect->id = 0;
	effect->timer = data->time + CLOCKS_PER_SEC / 2;
	effect->next = data->effects;
	data->effects = effect;
}

void	init_blow(t_data *data, t_vector pos, int delay)
{
	t_eff_list	*effect;

	effect = malloc(sizeof(t_eff_list));
	effect->sprite = push_front(&data->sprites, pos, '*', NULL);
	effect->arr = data->blow;
	effect->frame = 0;
	effect->id = 1;
	effect->timer = data->time + delay + CLOCKS_PER_SEC / 2;
	effect->next = data->effects;
	data->effects = effect;
}

void	bullet_effect(t_eff_list *effect, clock_t time)
{
	int			time_diff;

	time_diff = (int)(effect->timer - time);
	if (effect->frame == 0 && time_diff < CLOCKS_PER_SEC * 3 / 8)
	{
		effect->frame = 1;
		effect->sprite->tex = &effect->arr[1];
	}
	else if (effect->frame == 1 && time_diff < CLOCKS_PER_SEC / 4)
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

void	blow_effect(t_eff_list *effect, clock_t time)
{
	int			time_diff;

	time_diff = (int)(effect->timer - time);
	if (effect->frame == 0 && time_diff < CLOCKS_PER_SEC * 3 / 8)
	{
		effect->frame = 1;
		effect->sprite->tex = &effect->arr[0];
		system(BLOW_SOUND);
	}
	else if (effect->frame == 1 && time_diff < CLOCKS_PER_SEC / 4)
	{
		effect->frame = 2;
		effect->sprite->tex = &effect->arr[1];
	}
	else if (effect->frame == 2 && time_diff < CLOCKS_PER_SEC / 8)
	{
		effect->frame = 3;
		effect->sprite->tex = &effect->arr[2];
	}
	else if (effect->frame == 3 && time_diff < 0)
		effect->frame = -1;
}

void	delete_effect(t_eff_list **root,
			t_eff_list *effect, t_sprites *sprites)
{
	t_eff_list	*tmp;

	tmp = *root;
	if (tmp == NULL)
		return ;
	if (tmp == effect)
		*root = effect->next;
	else
		while (tmp->next && tmp->next != effect)
			tmp = tmp->next;
	if (tmp->next == effect)
		tmp->next = effect->next;
	delete_sprite(sprites, effect->sprite);
	free(effect);
}

void	show_effects(t_data *data)
{
	t_eff_list	*tmp;
	t_eff_list	*to_free;

	tmp = data->effects;
	while (tmp)
	{
		to_free = NULL;
		if (tmp->id == 0)
			bullet_effect(tmp, data->time);
		else if (tmp->id == 1)
			blow_effect(tmp, data->time);
		if (tmp->frame == -1)
			to_free = tmp;
		tmp = tmp->next;
		if (to_free)
			delete_effect(&data->effects, to_free, &data->sprites);
	}
}
