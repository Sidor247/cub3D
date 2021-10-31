/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:51:08 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/17 19:04:08 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_frame(t_image *img, t_data *data)
{
	draw_ceil(img, data->c_color);
	draw_floor(img, data->f_color);
	draw_walls(img, &data->player, data);
	draw_sprites(img, data);
}

int	loop_funcs(t_mlx *mlx)
{
	if (mlx->keys & 0x8000)
		mlx_stop(mlx);
	set_moves(&mlx->data.player, mlx->keys);
	move_player(&mlx->data.player, mlx->data.map);
	sort_sprites(&mlx->data.sprites, mlx->data.player.pos);
	render_frame(&mlx->img, &mlx->data);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	mlx_do_sync(mlx->ptr);
	return (1);
}

void	cub3d(char *file, int flag)
{
	t_mlx	mlx;

	mlx_start(&mlx, file);
	if (flag)
	{
		sort_sprites(&mlx.data.sprites, mlx.data.player.pos);
		render_frame(&mlx.img, &mlx.data);
		create_bmp(&mlx.img);
		mlx_stop(&mlx);
	}
	else
	{
		mlx.win = mlx_new_window(mlx.ptr,
				mlx.data.res.width, mlx.data.res.height, "cub3d");
		mlx_hook(mlx.win, 17, 0, mlx_stop, &mlx);
		mlx_hook(mlx.win, 2, 0, key_press, &mlx.keys);
		mlx_hook(mlx.win, 3, 0, key_release, &mlx.keys);
		mlx_loop_hook(mlx.ptr, loop_funcs, &mlx);
		mlx_loop(mlx.ptr);
	}
}

int	mlx_stop(t_mlx *mlx)
{
	clean_data(mlx);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2 && check_extension(argv[1], ".cub"))
		cub3d(argv[1], 0);
	if (argc == 3 && check_extension(argv[1], ".cub") && check_save(argv[2]))
		cub3d(argv[1], 1);
	print_error(-2);
	return (1);
}
