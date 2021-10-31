/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:53:48 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/17 19:04:30 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	image_init(t_mlx *mlx)
{
	t_image	*img;

	img = &mlx->img;
	img->res = mlx->data.res;
	img->ptr = mlx_new_image(mlx->ptr, img->res.width, img->res.height);
	if (img->ptr == NULL)
		return (1);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (0);
}

void	mlx_null(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
	mlx->img.ptr = NULL;
	mlx->keys = 0;
	mlx->data.res.width = -1;
	mlx->data.res.height = -1;
	mlx->data.c_color = 0xFF000000;
	mlx->data.f_color = 0xFF000000;
	mlx->data.map = NULL;
	mlx->data.dist_buf = NULL;
	mlx->data.sprites.start = NULL;
	mlx->data.sprites.end = NULL;
	mlx->data.textures[0].ptr = NULL;
	mlx->data.textures[1].ptr = NULL;
	mlx->data.textures[2].ptr = NULL;
	mlx->data.textures[3].ptr = NULL;
	mlx->data.textures[4].ptr = NULL;
	mlx->data.player.pos.x = -1;
	mlx->data.player.pos.y = -1;
}

void	mlx_start(t_mlx *mlx, char *file)
{
	mlx_null(mlx);
	mlx->ptr = mlx_init();
	if (mlx->ptr == NULL)
		mlx_error(mlx, 0);
	parser(mlx, file);
	if (image_init(mlx))
		mlx_error(mlx, 0);
	mlx->data.dist_buf = malloc(mlx->data.res.width * sizeof(float));
	if (mlx->data.dist_buf == NULL)
		mlx_error(mlx, 0);
}
