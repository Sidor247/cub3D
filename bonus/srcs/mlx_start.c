/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:53:48 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/28 16:59:39 by cwhis            ###   ########.fr       */
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

void	stats_init(t_stats *stats)
{
	stats->health = 100;
	stats->armor = 100;
	stats->ammo[0] = 100;
	stats->ammo[1] = 100;
	stats->max_ammo[0] = 400;
	stats->max_ammo[1] = 100;
	stats->c_weapon = 0;
	stats->weapons = 0x01;
}

void	mlx_null_data(t_data *data)
{
	int	i;

	data->res.width = -1;
	data->res.height = -1;
	data->map = NULL;
	data->dist_buf = NULL;
	data->sprites.start = NULL;
	data->sprites.end = NULL;
	data->effects = NULL;
	data->player.pos.x = -1;
	data->player.pos.y = -1;
	data->timer = 0;
	i = -1;
	while (++i < 64)
		data->textures[i].ptr = NULL;
	i = -1;
	while (++i < 6)
		data->items[i].ptr = NULL;
	i = -1;
	while (++i < 4)
		data->solid[i].ptr = NULL;
}

void	mlx_null(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
	mlx->img.ptr = NULL;
	mlx->keys = 0;
	mlx->mouse = 0;
	mlx_null_data(&mlx->data);
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
	stats_init(&mlx->data.stats);
}
