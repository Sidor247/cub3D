/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:53:14 by cwhis             #+#    #+#             */
/*   Updated: 2021/05/02 13:00:09 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_error(int code)
{
	if (code >= 0)
	{
		if (code > 0)
			errno = code;
		perror("Error\n");
	}
	else
		print_my_error(code);
}

void	print_my_error(int code)
{
	write(2, "Error\n", 6);
	if (code == -1)
		write(2, ": GNL said NO\n", 14);
	else if (code == -2)
		write(2, ": Invalid args\n", 15);
	else if (code == -3)
		write(2, ": Element was met twice\n", 24);
	else if (code == -4)
		write(2, ": Unknown identifier\n", 21);
	else if (code == -5)
		write(2, ": Invalid resolution\n", 21);
	else if (code == -6)
		write(2, ": Can't open texture\n", 21);
	else if (code == -7)
		write(2, ": Invalid color\n", 16);
	else if (code == -8)
		write(2, ": Insufficient data\n", 20);
	else if (code == -9)
		write(2, ": Invalid map\n", 14);
}

void	mlx_error(t_mlx *mlx, int code)
{
	clean_data(mlx);
	print_error(code);
	exit(1);
}

void	clean_data(t_mlx *mlx)
{
	int	i;

	i = -1;
	if (mlx->data.z_buf)
		free(mlx->data.z_buf);
	if (mlx->data.map)
		free_map(mlx->data.map);
	free_sprites(mlx->data.sprites.start);
	while (++i < 64)
		if (mlx->data.textures[i].ptr)
			mlx_destroy_image(mlx->ptr, mlx->data.textures[i].ptr);
	if (mlx->img.ptr)
		mlx_destroy_image(mlx->ptr, mlx->img.ptr);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
		free(mlx->ptr);
}
