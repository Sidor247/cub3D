/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atlas_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:01:00 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/26 21:08:09 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	get_image(void *mlx_ptr, t_image *atlas, char *s)
{
	while (*s == ' ')
		s++;
	if (check_extension(s, ".xpm"))
		atlas->ptr = mlx_xpm_file_to_image(mlx_ptr, s,
				&atlas->res.width, &atlas->res.height);
	else if (check_extension(s, ".png"))
		atlas->ptr = mlx_png_file_to_image(mlx_ptr, s,
				&atlas->res.width, &atlas->res.height);
	if (atlas->ptr == NULL)
		return (1);
	atlas->addr = mlx_get_data_addr(atlas->ptr, &atlas->bits_per_pixel,
			&atlas->line_length, &atlas->endian);
	return (0);
}

int	parse_image(void *mlx_ptr, t_image *img, t_image *atlas, t_point start)
{
	t_point			tmp;
	t_res			res;

	res = atlas->res;
	img->ptr = mlx_new_image(mlx_ptr, res.width, res.height);
	if (img->ptr == NULL)
		return (1);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
		&img->line_length, &img->endian);
	img->res = atlas->res;
	tmp.y = -1;
	while (++tmp.y < res.height)
	{
		tmp.x = -1;
		while (++tmp.x < res.width)
			*get_pix_addr(img, tmp) = *get_pix_addr(atlas,
				point(start.x + tmp.x, start.y + tmp.y));
	}
	return (0);
}

int	atlas_to_tex(t_mlx *mlx, t_image *atlas, t_image *arr, int n)
{
	t_image	*tmp;
	t_point	tmp_point;

	tmp = &arr[n];
	tmp->ptr = mlx_new_image(mlx->ptr, 64, 64);
	if (tmp->ptr == NULL)
		return (1);
	tmp->res.height = 64;
	tmp->res.width = 64;
	tmp->addr = mlx_get_data_addr(tmp->ptr, &tmp->bits_per_pixel,
			&tmp->line_length, &tmp->endian);
	tmp_point.y = -1;
	while (++tmp_point.y < 64)
	{
		tmp_point.x = -1;
		while (++tmp_point.x < 64)
			*get_pix_addr(tmp, tmp_point) = *get_pix_addr(atlas,
				point(tmp_point.x + n % 6 * 64, tmp_point.y + n / 6 * 64));
	}
	return (0);
}
