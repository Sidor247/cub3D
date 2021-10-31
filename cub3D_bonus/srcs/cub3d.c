/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:51:08 by cwhis             #+#    #+#             */
/*   Updated: 2021/10/31 18:13:43 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_frame(t_image *img, t_data *data)
{
	t_player	*player;

	player = &data->player;
	clean_stencil_buf(img);
	draw_hud(img, data);
	draw_weapon(img, data);
	draw_sprites(img, data);
	draw_walls(img, data);
	draw_ceil(img, WHITE);
	draw_tex_floor(img, player->dir, player->pos, &data->textures[FLOOR_NUM]);
}

int	loop_funcs(t_mlx *mlx)
{
	clock_t	time;

	if (mlx->keys & 0x80000000)
		mlx_stop(mlx);
	if (mlx->keys & 0x40000000)
		mouse_free(&mlx->mouse);
	if (mlx->mouse & 0x8000)
		mouse_rotation(mlx);
	if (mlx->mouse & 0x01)
		shoot_request(&mlx->data);
	if (mlx->data.timer)
		shoot(&mlx->data);
	else
		set_weapon(&mlx->data.stats, mlx->keys);
	set_moves(&mlx->data.player, mlx->keys);
	move_player(mlx);
	raycating(&mlx->data);
	show_effects(&mlx->data);
	sort_sprites(&mlx->data.sprites, mlx->data.player.pos);
	render_frame(&mlx->img, &mlx->data);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	time = clock();
	if (FPS)
		show_fps(mlx, time);
	mlx->data.time = time;
	mlx_do_sync(mlx->ptr);
	return (1);
}

void	cub3d(char *file, int flag)
{
	t_mlx	mlx;

	mlx_start(&mlx, file);
	if (flag)
	{
		raycating(&mlx.data);
		sort_sprites(&mlx.data.sprites, mlx.data.player.pos);
		render_frame(&mlx.img, &mlx.data);
		create_bmp(&mlx.img);
		mlx_stop(&mlx);
	}
	else
	{
		mlx.win = mlx_new_window(mlx.ptr,
				mlx.data.res.width, mlx.data.res.height, "cub3D");
		mlx_hook(mlx.win, 17, 0, mlx_stop, &mlx);
		mlx_hook(mlx.win, 2, 0, key_press, &mlx.keys);
		mlx_hook(mlx.win, 3, 0, key_release, &mlx.keys);
		mlx_hook(mlx.win, 12, 0, mouse_grab, &mlx.mouse);
		mlx_hook(mlx.win, 4, 0, button_press, &mlx.mouse);
		mlx_hook(mlx.win, 5, 0, button_release, &mlx.mouse);
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
