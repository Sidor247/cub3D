/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorlebedev <igorlebedev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 09:21:00 by igorlebedev       #+#    #+#             */
/*   Updated: 2021/02/09 22:37:31 by igorlebedev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_square(t_image *img, int x, int y, int size, int color)
{
	char	*dst;
	int		i;
	int		j;

	i = -(size / 2);
	j = -(size / 2);
	while (j < size / 2)
	{
		while(i < size / 2)
		{
			dst = img->addr + (y + j) * img->line_length +
			(x + i) * (img->bits_per_pixel / 8);
			*(unsigned int*)dst = color;
			i++;
		}
		i = -(size / 2);
		j++;
	}
}

void	put_line(t_image *img, int x, int y, int length, float angle, int color)
{
	char	*dst;
	int		i;

	i = 0;
	while (i < length)
	{
		dst = img->addr + (y + (int)((float)i * sinf(angle))) * img->line_length +
		(x + (int)((float)i * cosf(angle))) * (img->bits_per_pixel / 8);
		*(unsigned int*)dst = color;
		i++;
	}
}

void	draw_map(t_image *img, char **map)
{
	int	i = 0;
	int	j = 0;
	int x = 20;
	int y = 20;

	while (map[j])
	{
		while (map[j][i])
		{
			if (map[j][i] == '1')
				put_square(img, x, y, 20, 0x000000FF);
			else
				put_square(img, x, y, 20, 0x00000000);
			i++;
			x += 20;
		}
		i = 0;
		x = 20;
		j++;
		y += 20;
	}
}

void	draw_player(t_image *img, t_player *player)
{
	put_square(img, 20 + (int)(player->x * 20),
	20 + (int)(player->y * 20), (int)(20 * COL_SIZE), 0x0000FF00);
	put_line(img, 20 + (int)(player->x * 20),
	20 + (int)(player->y * 20), 50, player->dir, 0x00FF0000);
}


int		player_init(char **map, t_player *player)
{
	int		i;
	int		j;
	int 	k;
	char	*s;

	i = -1;
	j = -1;
	s = "ESWN";
	while (map[++j])
	{
		while (map[j][++i])
		{
			if (ft_strchr(s, map[j][i]))
			{
				player->x = (float)i;
				player->y = (float)j;
				k = 0;
				while (s[k] != map[j][i])
					k++;
				player->dir = (float)k * M_PI_2;
				player->x_speed = 0;
				player->y_speed = 0;
				player->z_speed = 0;
				return (1);
			}
		}
		i = -1;
	}
	return (-1);
}

void	move_player(t_player *player)
{
	if (player->y_speed)
		player->y += (float)(player->y_speed) * SPEED;
	if (player->x_speed)
		player->x += (float)(player->x_speed) * SPEED;
	if (player->z_speed)
		player->dir += (float)(player->z_speed) * ROT;
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
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.img, 0, 0);
	return (1);
}

int		mlx_staff(t_mlx *mlx)
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
		mlx->player.y_speed = -1;
	else if (key == S)
		mlx->player.y_speed = 1;
	else if (key == A)
		mlx->player.x_speed = -1;
	else if (key == D)
		mlx->player.x_speed = 1;
	else if (key == LEFT)
		mlx->player.z_speed = -1;
	else if (key == RIGHT)
		mlx->player.z_speed = 1;
	return (key);
}

int		key_release(int key, t_mlx *mlx)
{
	if (key == W || key == S)
		mlx->player.y_speed = 0;
	else if (key == A || key == D)
		mlx->player.x_speed = 0;
	if (key == LEFT || key == RIGHT)
		mlx->player.z_speed = 0;
	return (1);
}

int		main(int argc, char **argv)
{
	t_mlx		mlx;

	if (argc == 2)
		mlx.map = parser(argv[1]);
	mlx_staff(&mlx);
	mlx_hook(mlx.win, 2, 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 0, key_release, &mlx);
	mlx_loop_hook(mlx.ptr, render_frame, &mlx);
	mlx_loop(mlx.ptr);
}
