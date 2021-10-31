/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:50:52 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/17 19:05:18 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"	

int	get_map(char ***map, t_list *lines, t_list *first)
{
	t_list	*tmp;
	char	**tmp_map;
	int		size;
	int		i;

	size = ft_lstsize(first);
	tmp_map = malloc((size + 1) * sizeof(char *));
	if (tmp_map == NULL)
		return (1);
	i = 0;
	tmp_map[size] = NULL;
	tmp = lines;
	while (tmp->next != first)
		tmp = tmp->next;
	while (i < size)
	{
		tmp_map[i] = first->content;
		first = first->next;
		i++;
	}
	ft_lstclear(&tmp->next, none);
	*map = tmp_map;
	return (0);
}

void	direction_init(t_vector *dir, char c)
{
	if (c == 'N' || c == 'S')
	{
		if (c == 'S')
			dir->y = 1;
		else
			dir->y = -1;
	}
	else
		dir->y = 0;
	if (c == 'E' || c == 'W')
	{
		if (c == 'E')
			dir->x = 1;
		else
			dir->x = -1;
	}
	else
		dir->x = 0;
}

void	position_init(char **map, t_player *player)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (ft_strchr("ESWN", map[j][i]))
			{
				player->pos.x = (float)i + 0.5;
				player->pos.y = (float)j + 0.5;
				direction_init(&player->dir, map[j][i]);
				update_plane(player);
				return ;
			}
		}
	}
}

int	parse_map(t_data *data, t_list *lines, t_list *first)
{
	if (check_data(data))
		return (-8);
	if (check_map_tail(first))
		return (-9);
	if (get_map(&data->map, lines, first))
		return (0);
	if (check_map_chars(data->map) || check_map_bounds(data->map))
		return (-9);
	if (sprites_init(&data->sprites, data->map))
		return (0);
	position_init(data->map, &data->player);
	return (2);
}
