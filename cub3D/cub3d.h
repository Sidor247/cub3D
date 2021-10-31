/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:51:16 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/30 01:42:58 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "srcs/libft/libft.h"
# include "mlx/mlx.h"
# include "srcs/gnl/get_next_line.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

# define COL_SIZE 0.3
# define SPEED 0.15
# define ROT 0.07
# define FOV 85.0

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define L_SHIFT 257
# define R_SHIFT 258

# define RED 0xFFFF0000
# define GREEN 0xFF00FF00
# define BLUE 0xF00000FF
# define BLACK 0x00000000
# define WHITE 0xF0FFFFFF

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_vector
{
	float	x;
	float	y;
}				t_vector;

typedef struct s_res
{
	int	width;
	int	height;
}				t_res;

typedef struct s_sprite
{
	t_vector		pos;
	struct s_sprite	*next;
	struct s_sprite	*prev;
}				t_sprite;

typedef struct s_sprites
{
	t_sprite	*start;
	t_sprite	*end;
}				t_sprites;

typedef struct s_dda
{
	t_point	mapPoint;
	float	sideDistX;
	float	sideDistY;
	float	deltaDistX;
	float	deltaDistY;
	int		stepX;
	int		stepY;
}				t_dda;

typedef struct s_sdraw
{
	t_point	draw_start;
	t_point	draw_end;
	t_point	tex;
	int		size;
	int		spriteScreenX;
}				t_sdraw;

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	t_res	res;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	int			move;
	int			strafe;
	int			rotate;
	int			run;
}				t_player;

typedef struct s_data
{
	t_res			res;
	t_image			textures[5];
	t_sprites		sprites;
	t_player		player;
	unsigned int	c_color;
	unsigned int	f_color;
	char			**map;
	float			*dist_buf;
}				t_data;

typedef struct s_mlx
{
	t_image	img;
	t_data	data;
	int		keys;
	void	*ptr;
	void	*win;
}				t_mlx;

void		parser(t_mlx *mlx, char *file);
int			parse_something(t_mlx *mlx, char *s);
int			parse_res(void *mlx_ptr, t_res *res, char *s);
int			parse_tex(void *mlx_ptr, t_image *img, char *s);
int			parse_color(unsigned int *color, char *tmp);
int			parse_map(t_data *data, t_list *lines, t_list *first);
int			parse_and_trim(t_mlx *mlx, char *line);
int			file_to_list(t_list **lines, char *file);
t_list		*get_list(int fd);
int			get_map(char ***map, t_list *lines, t_list *first);

void		put_square(t_image *img, t_point center, int size, int color);
void		put_line(t_image *img, t_point point, t_vector line, int color);
void		draw_map(t_image *img, char **map);
void		draw_player(t_image *img, t_player *player, char **map);
void		draw_rays(t_image *img, t_player *player, char **map);

void		rotate_player(t_vector *dir, float a);
void		collision_check(t_vector *pos, t_vector delta, char **map);
void		move_player(t_player *player, char **map);

void		set_moves(t_player *player, int keys);
int			key_press(int key, int *keys);
int			key_release(int key, int *keys);

void		set_dir(t_vector *dir, char c);
void		position_init(char **map, t_player *player);
void		direction_init(t_vector *dir, char c);
int			image_init(t_mlx *mlx);

void		mlx_start(t_mlx *mlx, char *file);
void		cub3d(char *file, int flag);
void		render_frame(t_image *img, t_data *data);
int			loop_funcs(t_mlx *mlx);
int			mlx_stop(t_mlx *mlx);

void		dda_init(t_dda *dda, t_vector dir, t_vector pos);
float		dda(t_vector dir, t_vector pos, char **map, char *side);
int			get_height(t_vector ray, t_vector pos, t_data *data, int *color);
t_vector	get_tex_data(t_vector ray, t_vector pos,
				t_data *data, t_image **tex);

void		put_tex_stripe(t_image *img, int x, t_vector trash, t_image *tex);
void		draw_ceil(t_image *img, unsigned int color);
void		draw_floor(t_image *img, unsigned int color);
void		draw_walls(t_image *img, t_player *player, t_data *data);

int			push_front(t_sprites *sprites, float x, float y);
int			sprites_init(t_sprites *sprites, char **map);
void		draw_sprites(t_image *img, t_data *data);

int			sprite_cmp(t_vector a, t_vector b, t_vector pos);
void		swap_sprites(t_sprites *sprites, t_sprite *a);
void		sort_sprites(t_sprites *sprites, t_vector pos);

unsigned *get_pix_addr(t_image *img, int x, int y);
void		none(void *ptr);
void		update_plane(t_player *player);
int			count_digits(char **s);

void		mlx_null(t_mlx *mlx);

void		mlx_error(t_mlx *mlx, int code);
void		print_error(int code);
void		print_my_error(int code);

void		clean_data(t_mlx *mlx);
void		free_map(char **map);
void		free_sprites(t_sprite *start);

int			check_extension(char *file, char *ex);
int			check_save(char *str);
int			check_map_tail(t_list *first);
int			check_data(t_data *data);
int			check_map_chars(char **map);
int			check_map_bounds(char **map);
int			check_map_string(char *s);
int			check_map_column(char **map, size_t i);

void		create_bmp(t_image *img);
void		write_pixel_data(int fd, t_image *img);
void		write_le_num(unsigned char *dst, unsigned int num);

#endif