/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:50:20 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/28 00:58:44 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	parse_res(void *mlx_ptr, t_res *res, char *s)
{
	int		dig_count;
	int		a[2];
	int		i;

	if (res->width != -1 || res->height != -1)
		return (-3);
	i = -1;
	while (++i < 2)
	{
		while (*s == ' ')
			s++;
		a[i] = ft_atoi(s);
		dig_count = 0;
		dig_count = count_digits(&s);
		if (dig_count > 9)
			return (-5);
	}
	if (a[0] < 1 || a[1] < 1 || *s)
		return (-5);
	mlx_get_screen_size(mlx_ptr, &res->width, &res->height);
	if (a[0] < res->width)
		res->width = a[0];
	if (a[1] < res->height)
		res->height = a[1];
	return (1);
}

int	parse_atlas(t_mlx *mlx, t_image *arr, int n, char *s)
{
	t_image	atlas;
	int		i;

	if (get_image(mlx->ptr, &atlas, s))
		return (-6);
	i = -1;
	while (++i < n)
		if (atlas_to_tex(mlx, &atlas, arr, i))
			break ;
	mlx_destroy_image(mlx->ptr, atlas.ptr);
	if (i != n)
		return (-6);
	else
		return (1);
}

int	parse_something(t_mlx *mlx, char *s)
{
	if (ft_strnstr(s, "R ", 2))
		return (parse_res(mlx->ptr, &mlx->data.res, s + 2));
	else if (ft_strnstr(s, "TEX ", 4))
		return (parse_atlas(mlx, mlx->data.textures, 64, s + 4));
	else if (ft_strnstr(s, "ITEMS ", 6))
		return (parse_atlas(mlx, mlx->data.items, 6, s + 6));
	else if (ft_strnstr(s, "SOLID ", 6))
		return (parse_atlas(mlx, mlx->data.solid, 4, s + 6));
	else if (ft_strnstr(s, "HUD ", 4))
		return (parse_hud(mlx, s + 4));
	else if (ft_strnstr(s, "CG ", 3))
		return (parse_chaingun(mlx->ptr, &mlx->data.weapons[0], s + 3));
	else if (ft_strnstr(s, "RL ", 3))
		return (parse_rocket_launcher(mlx->ptr, &mlx->data.weapons[1], s + 3));
	else if (ft_strnstr(s, "BULLET ", 7))
		return (parse_bullets(mlx->ptr, mlx->data.bullet, s + 7));
	return (2);
}

void	parser(t_mlx *mlx, char *file)
{
	t_list	*lines;
	t_list	*tmp;
	int		code;

	if (file_to_list(&lines, file))
		mlx_error(mlx, 0);
	tmp = lines;
	while (tmp)
	{
		code = parse_and_trim(mlx, tmp->content);
		if (code != 1)
			break ;
		tmp = tmp->next;
	}
	if (code == 2)
		code = parse_map(&mlx->data, lines, tmp);
	ft_lstclear(&lines, free);
	if (code != 2)
		mlx_error(mlx, code);
}
