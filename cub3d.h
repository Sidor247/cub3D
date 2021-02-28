/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 10:35:50 by igorlebedev       #+#    #+#             */
/*   Updated: 2021/02/28 19:50:57 by cwhis            ###   ########.fr       */
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

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define BLACK 0x00000000

typedef	struct	s_point
{
	int x;
	int y;
}				t_point;

typedef	struct	s_vector
{
	float x;
	float y;
}				t_vector;

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
	t_vector	pos;
	t_vector	dir;
	int			keys;
	int			move;
	int			strafe;
	int			rotate;
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