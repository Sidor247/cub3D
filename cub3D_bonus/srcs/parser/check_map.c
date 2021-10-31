/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 00:33:09 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/26 12:04:40 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_map_string(char *s)
{
	int	flag;

	flag = 2;
	while (*s)
	{
		if (ft_strchr("123456789", *s))
			flag = 1;
		else if (*s == ' ')
		{
			if (flag == 0)
				return (1);
			flag = 2;
		}
		else
		{
			if (flag == 2)
				return (1);
			flag = 0;
		}
		s++;
	}
	if (flag == 0)
		return (1);
	return (0);
}

int	check_map_column(char **map, size_t i)
{
	int		j;
	int		flag;

	j = -1;
	flag = 2;
	while (map[++j])
	{
		if (ft_strlen(map[j]) <= i || map[j][i] == ' ')
		{
			if (flag == 0)
				return (1);
			flag = 2;
		}
		else if (ft_strchr("123456789", map[j][i]))
			flag = 1;
		else
		{
			if (flag == 2)
				return (1);
			flag = 0;
		}
	}
	if (flag == 0)
		return (1);
	return (0);
}

int	check_map_tail(t_list *first)
{
	t_list	**empty;
	t_list	*tmp;

	tmp = first;
	empty = NULL;
	while (tmp->next && empty == NULL)
	{
		if (*(char *)(tmp->next->content) == '\0')
			empty = &tmp->next;
		tmp = tmp->next;
	}
	if (empty)
	{
		tmp = *empty;
		while (tmp->next)
		{
			if (*(char *)(tmp->next->content) != '\0')
				return (1);
			tmp = tmp->next;
		}
		ft_lstclear(empty, free);
	}
	return (0);
}

int	check_player_pos(char **map)
{
	int	i;
	int	j;
	int	flag;

	j = -1;
	flag = 0;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{		
			if (ft_strchr("NSWE", map[j][i]))
				flag++;
		}
	}
	if (flag != 1)
		return (1);
	return (0);
}

int	check_map_bounds(char **map)
{
	size_t	max_len;
	size_t	tmp_len;
	int		i;

	i = -1;
	max_len = 0;
	while (map[++i])
	{
		if (check_map_string(map[i]))
			return (1);
		tmp_len = ft_strlen(map[i]);
		if (tmp_len > max_len)
			max_len = tmp_len;
	}
	tmp_len = -1;
	while (++tmp_len < max_len)
		if (check_map_column(map, tmp_len))
			return (1);
	return (0);
}
