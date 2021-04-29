/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 00:49:12 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/28 10:26:42 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_sprite	*push_front(t_sprites *sprites, t_vector pos, char id, t_image *tex)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (sprite == NULL)
		return (NULL);
	sprite->pos = pos;
	sprite->tex = tex;
	sprite->id = id;
	sprite->prev = NULL;
	sprite->next = sprites->start;
	if (sprites->end == NULL)
		sprites->end = sprite;
	else
		sprites->start->prev = sprite;
	sprites->start = sprite;
	return (sprite);
}

int	sprites_init(t_data *data)
{
	t_sprite	*tmp;
	char		**map;
	int			i;
	int			j;

	map = data->map;
	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (ft_strchr("abcdef", map[j][i]))
				tmp = push_front(&data->sprites, vector(i + 0.5, j + 0.5),
					map[j][i], &data->items[map[j][i] - 'a']);
			else if (ft_strchr("ABCD", map[j][i]))
				tmp = push_front(&data->sprites, vector(i + 0.5, j + 0.5),
					map[j][i], &data->solid[map[j][i] - 'A']);
			else
				continue ;
			if (tmp == NULL)
				return (1);
		}
	}
	return (0);
}

void	delete_sprite(t_sprites *sprites, t_sprite *sprite)
{
	if (sprite->next)
		sprite->next->prev = sprite->prev;
	else
		sprites->end = sprite->prev;
	if (sprite->prev)
		sprite->prev->next = sprite->next;
	else
		sprites->start = sprite->next;
	free(sprite);
}