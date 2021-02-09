/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorlebedev <igorlebedev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 10:35:50 by igorlebedev       #+#    #+#             */
/*   Updated: 2021/02/09 22:01:58 by igorlebedev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "libft/libft.h"
#include "mlx/mlx.h"
#include "gnl/get_next_line.h"
#include <math.h>
#include <fcntl.h>
#include <stdio.h>

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define COL_SIZE 0.25
# define SPEED 0.1
# define ROT 0.1

typedef struct  s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}               t_image;

typedef	struct	s_player
{
	float	x;
	float	y;
	float	dir;
	int		x_speed;
	int		y_speed;
	int		z_speed;
}				t_player;

typedef struct  s_mlx
{
	t_player	player;
	t_image		img;
	char		**map;
	void		*ptr;
    void		*win;
}				t_mlx;

void	none(void *ptr);
t_list	*get_list(int fd);
char	**get_map(int fd);
char	**parser(char *file);

#endif