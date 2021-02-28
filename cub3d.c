/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 09:21:00 by igorlebedev       #+#    #+#             */
/*   Updated: 2021/02/28 20:47:45 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dir(t_vector *player, char c)
{
	if (c == 'N' || c == 'S')
		player->dir.y = (c == 'S') ? 1 : -1;
	else
		player->dir.y = 0;
	if (c == 'E' || c == 'W')
		player->dir.x = (c == 'E') ? 1 : -1;
	else
		player->dir.x = 0;
}

int		pos_init(char **map, t_player *player)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (map[++j])
	{
		while (map[j][++i])
		{
			if (ft_strchr("ESWN", map[j][i]))
			{
				player->pos.x = (float)i;
				player->pos.y = (float)j;
				set_dir(player, map[j][i]);
				return (1);
			}
		}
		i = -1;
	}
	return (-1);
}

int		player_init(t_player *player, char **map)
{
	player->keys = 0x00000000;
	player->move = 0;
	player->strafe = 0;
	player->rotate = 0;
	return (pos_init(map, player));
}

int		render_frame(t_mlx *mlx)
{
	move_player(&mlx->player);
	draw_map(&(mlx->img), mlx->map);
	draw_player(&(mlx->img), &(mlx->player));
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.img, 0, 0);
	return (1);
}

int		image_init(t_mlx *mlx)
{
	mlx->img.img = mlx_new_image(mlx->ptr, 800, 600);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &(mlx->img.bits_per_pixel),
	&(mlx->img.line_length), &(mlx->img.endian));
	render_frame(mlx);
	return (1);
}

int		mlx_start(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, 800, 600, "cub3d");
	player_init(mlx->map, &(mlx->player));
	image_init(mlx);
	return (1);
}

int		key_press(int key, t_mlx *mlx)
{
	if (key == W)
		mlx->player.keys |= 0x01;
	else if (key == S)
		mlx->player.keys |= 0x02;
	else if (key == D)
		mlx->player.keys |= 0x04;
	else if (key == A)
		mlx->player.keys |= 0x08;
	else if (key == RIGHT)
		mlx->player.keys |= 0x10;
	else if (key == LEFT)
		mlx->player.keys |= 0x20;
	return (1);
}

int		key_release(int key, t_mlx *mlx)
{
	if (key == W)
		mlx->player.keys &= ~0x01;
	else if (key == S)
		mlx->player.keys &= ~0x02;
	else if (key == D)
		mlx->player.keys &= ~0x04;
	else if (key == A)
		mlx->player.keys &= ~0x08;
	else if (key == RIGHT)
		mlx->player.keys &= ~0x10;
	else if (key == LEFT)
		mlx->player.keys &= ~0x20;
	return (1);
}

void	move_player(t_player *player)
{
	if (player->move)
	{
		player->x += (float)(player->move) * cosf(player->dir) * SPEED;
		player->y += (float)(player->move) * sinf(player->dir) * SPEED;
	}
	if (player->strafe)
	{
		player->x += (float)(player->strafe) * sinf(-player->dir) * SPEED;
		player->y += (float)(player->strafe) * cosf(-player->dir) * SPEED;
	}
	if (player->rotate)
		player->dir += (float)(player->rotate) * ROT;
}
int		main(int argc, char **argv)
{
	t_mlx		mlx;

	if (argc == 2)
		mlx.map = parser(argv[1]);
	mlx_start(&mlx);
	mlx_hook(mlx.win, 2, 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 0, key_release, &mlx);
	mlx_loop_hook(mlx.ptr, render_frame, &mlx);
	mlx_loop(mlx.ptr);
}
