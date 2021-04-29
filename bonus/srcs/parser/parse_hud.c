/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 10:10:18 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/26 21:06:20 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	parse_digits(void *mlx_ptr, t_image *arr, t_image *atlas, t_point start)
{
	t_point			tmp;
	t_res			res;
	int				i;

	i = -1;
	res = atlas->res;
	while (++i < 10)
	{
		arr[i].ptr = mlx_new_image(mlx_ptr, res.width, res.height);
		if (arr[i].ptr == NULL)
			return (1);
		arr[i].addr = mlx_get_data_addr(arr[i].ptr, &arr[i].bits_per_pixel,
			&arr[i].line_length, &arr[i].endian);
		arr[i].res = atlas->res;
		tmp.y = -1;
		while (++tmp.y < res.height)
		{
			tmp.x = -1;
			while (++tmp.x < res.width)
				*get_pix_addr(&arr[i], tmp) = *get_pix_addr(atlas,
					point(start.x + tmp.x, start.y + tmp.y));
		}
		start.x += atlas->res.width + 1;
	}
	return (0);
}

int	parse_hud(t_mlx *mlx, char *s)
{
	t_image	atlas;

	if (get_image(mlx->ptr, &atlas, s))
		return (-6);
	atlas.res = res(3, 5);
	if (parse_digits(mlx->ptr, mlx->data.hud.small, &atlas, point(1, 1)))
		return (-6);
	atlas.res = res(4, 6);
	if (parse_digits(mlx->ptr, mlx->data.hud.med_d, &atlas, point(1, 8)))
		return (-6);
	if (parse_digits(mlx->ptr, mlx->data.hud.med_l, &atlas, point(1, 14)))
		return (-6);
	atlas.res = res(14, 16);
	if (parse_digits(mlx->ptr, mlx->data.hud.big, &atlas, point(51, 1)))
		return (-6);
	if (parse_image(mlx->ptr, &mlx->data.hud.big[10], &atlas, point(201, 1)))
		return (-6);
	atlas.res = res(320, 32);
	if (parse_image(mlx->ptr, &mlx->data.hud.back, &atlas, point(0, 21)))
		return (-6);
	mlx_destroy_image(mlx->ptr, atlas.ptr);
	return (1);
}
