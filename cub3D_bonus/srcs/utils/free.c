/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:51:33 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/25 23:24:07 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_sprites(t_sprite *start)
{
	t_sprite	*tmp;
	t_sprite	*next;

	tmp = start;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}
