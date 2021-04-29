/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_weapons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:40:28 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/28 00:39:47 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	parse_chaingun(void *mlx_ptr, t_weapon *weapon, char *s)
{
	t_image	atlas;
	int		i;

	if (get_image(mlx_ptr, &atlas, s))
		return (-6);
	weapon->tex = malloc(3 * sizeof(t_image));
	if (weapon->tex == NULL)
		return (0);
	weapon->frame = 0;
	atlas.res = res(114, 103);
	i = -1;
	while (++i < 3)
		if (parse_image(mlx_ptr, &weapon->tex[i], &atlas,
			point(i * 114, 0)))
			break;
	mlx_destroy_image(mlx_ptr, atlas.ptr);
	if (i != 3)
		return (0);
	else
		return (1);
}

int	parse_rocket_launcher(void *mlx_ptr, t_weapon *weapon, char *s)
{
	t_image	atlas;
	int		i;

	if (get_image(mlx_ptr, &atlas, s))
		return (-6);
	weapon->tex = malloc(5 * sizeof(t_image));
	if (weapon->tex == NULL)
		return (0);
	weapon->frame = 0;
	atlas.res = res(102, 120);
	i = -1;
	while (++i < 5)
		if (parse_image(mlx_ptr, &weapon->tex[i], &atlas,
			point(i * 102, 0)))
			break;
	mlx_destroy_image(mlx_ptr, atlas.ptr);
	if (i != 5)
		return (0);
	else
		return (1);
}

int	parse_bullets(void *mlx_ptr, t_image *arr, char *s)
{
	t_image	atlas;
	int		i;

	if (get_image(mlx_ptr, &atlas, s))
		return (-6);
	atlas.res = res(64, 64);
	i = -1;
	while (++i < 4)
		if (parse_image(mlx_ptr, &arr[i], &atlas,
			point(i * 64, 0)))
			break;
	mlx_destroy_image(mlx_ptr, atlas.ptr);
	if (i != 4)
		return (0);
	else
		return (1);
}
