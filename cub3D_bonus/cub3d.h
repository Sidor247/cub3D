/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:51:16 by cwhis             #+#    #+#             */
/*   Updated: 2021/10/31 17:57:53 by cwhis            ###   ########.fr       */
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
# include <time.h>

# include "settings.h"

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
# define DIG_1 18
# define DIG_2 19
# define BCKSP 51

# define BUTTON_1 1
# define BUTTON_2 2
# define BUTTON_3 3
# define BUTTON_4 4
# define BUTTON_5 5

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF

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

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	char	**stencil_buf;
	t_res	res;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct	s_tex_data
{
	t_image	*tex;
	float	x;
}				t_tex_data;

typedef struct s_sprite
{
	t_vector		pos;
	t_image			*tex;
	char			id;
	struct s_sprite	*next;
	struct s_sprite	*prev;
}				t_sprite;

typedef struct s_sprites
{
	t_sprite	*start;
	t_sprite	*end;
}				t_sprites;

typedef struct s_eff_list
{
	t_sprite			*sprite;
	t_image				*arr;
	clock_t				timer;
	int					frame;
	int					id;
	struct s_eff_list	*next;
}				t_eff_list;

typedef struct s_hud
{
	t_image	big[11];
	t_image	med_l[10];
	t_image	med_d[10];
	t_image	small[10];
	t_image	back;
}				t_hud;

typedef	struct s_weapon
{
	t_image	*tex;
	int		frame;
}				t_weapon;

typedef struct s_stats
{
	int	health;
	int	armor;
	int	weapons;
	int c_weapon;
	int ammo[2];
	int	max_ammo[2];
}				t_stats;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	int			move;
	int			strafe;
	int			rotate;
	int			run;
}				t_player;

typedef struct s_data
{
	t_image			textures[64];
	t_image			items[6];
	t_image			solid[4];
	t_image			bullet[4];
	t_image			blow[3];
	t_weapon		weapons[2];
	t_hud			hud;
	t_sprites		sprites;
	t_eff_list		*effects;
	t_player		player;
	t_stats			stats;
	char			**map;
	char			**stencil_buf;
	float			*z_buf;
	t_tex_data		*tex_data;
	t_res			res;
	clock_t			timer;
	clock_t			time;
}				t_data;

typedef struct s_mlx
{
	t_image	img;
	t_data	data;
	int		mouse;
	int		keys;
	void	*ptr;
	void	*win;
}				t_mlx;

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
	int		size;
	t_point	c_draw_start;
	t_point	c_draw_end;
	t_point	draw_start;
	t_point	draw_end;
}				t_sdraw;

void		parser(t_mlx *mlx, char *file);
int			parse_hud(t_mlx *mlx, char *s);
int			parse_color(unsigned int *color, char *tmp);
int			parse_map(t_data *data, t_list *lines, t_list *first);
int			parse_and_trim(t_mlx *mlx, char *line);
int			parse_something(t_mlx *mlx, char *s);
int			parse_chaingun(void *mlx_ptr, t_weapon *weapon, char *s);
int			parse_rocket_launcher(void *mlx_ptr, t_weapon *weapon, char *s);
int			parse_bullets(void *mlx_ptr, t_image *arr, char *s);
int			parse_blow(void *mlx_ptr, t_image *arr, char *s);
int			atlas_to_tex(t_mlx *mlx, t_image *atlas, t_image *arr, int n);
int			file_to_list(t_list **lines, char *file);
int			get_image(void *mlx_ptr, t_image *atlas, char *s);
int			parse_image(void *mlx_ptr, t_image *img, t_image *atlas, t_point start);
t_list		*get_list(int fd);

void		put_square(t_image *img, t_point center, int size, int color);
void		put_line(t_image *img, t_point point, t_vector line, int color);
void		draw_map(t_image *img, char **map);
void		draw_player(t_image *img, t_player *player, char **map);
void		draw_rays(t_image *img, t_player *player, char **map);

void		rotate_player(t_vector *dir, float a);
void		wall_collisions(t_vector pos, t_vector *delta, char **map);
void		obj_collisions(t_vector pos, t_vector *delta, t_mlx *mlx);
void		move_player(t_mlx *mlx);
void		set_moves(t_player *player, int keys);
void		set_weapon(t_stats *stats, int keys);

int			key_press(int key, int *keys);
int			key_release(int key, int *keys);
int			mouse_motion(int x, int y, t_mlx *mlx);

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
float		dda(t_vector ray, t_vector pos, char **map, char *tex_id);
int			get_height(t_vector ray, t_vector pos, t_data *data, int *color);
float		get_ray_data(t_vector ray, t_vector pos,
				t_data *data, t_tex_data *tex_data);
void		raycating(t_data *data);

void		draw_ceil(t_image *img, unsigned int color);
void		draw_floor(t_image *img, unsigned int color);
void		draw_walls(t_image *img, t_data *data);
void		draw_element(t_image *img, t_image *element, t_point start);
void		draw_weapon(t_image *img, t_data *data);
void		draw_hud(t_image *img, t_data *data);

t_sprite	*push_front(t_sprites *sprites, t_vector pos, char id, t_image *tex);
int			sprites_init(t_data *data);
void		delete_sprite(t_sprites *sprites, t_sprite *sprite);
void		draw_sprites(t_image *img, t_data *data);

int			sprite_cmp(t_vector a, t_vector b, t_vector pos);
void		swap_sprites(t_sprites *sprites, t_sprite *a);
void		sort_sprites(t_sprites *sprites, t_vector pos);

unsigned	*get_pix_addr(t_image *img, t_point point);
void		none(void *ptr);
t_vector	get_plane(t_vector dir);
int			count_digits(char **s);
void		show_fps(t_mlx *mlx, clock_t now);

void		mlx_error(t_mlx *mlx, int code);
void		print_error(int code);
void		print_my_error(int code);

void		clean_data(t_mlx *mlx);
void		free_map(char **map);
void		free_sprites(t_sprite *start);

int			check_extension(char *file, char *ex);
int			check_save(char *str);
int			check_data(t_data *data);

int			check_map_tail(t_list *first);
int			check_player_pos(char **map);
int			check_map_bounds(char **map);

void		create_bmp(t_image *img);

void		mouse_rotation(t_mlx *mlx);
int			mouse_grab(int *mouse);
int			mouse_free(int *mouse);
int			button_press(int button, int x, int y, int *mouse);
int			button_release(int button, int x, int y, int *mouse);

void		draw_tex_floor(t_image *img,
				t_vector dir, t_vector pos, t_image *tex);

t_vector	add_vec(t_vector a, t_vector b);
t_vector	mult_vec(float k, t_vector vec);
t_vector	sub_vec(t_vector a, t_vector b);
t_vector	vector(float x, float y);

t_point		point(int x, int y);
t_res		res(int width, int height);

void		pick(t_mlx *mlx, t_sprite *sprite);
void		shoot_request(t_data *data);
void		shoot(t_data *data);
void		hit_scan(t_data *data);
void		chaingun(t_data *data);
void		projectile(t_data *data);
void		rocket_launcher(t_data *data);
void		show_effects(t_data *data);
void		init_bullet(t_data *data, t_vector pos);
void		init_blow(t_data *data, t_vector pos, int delay);
void		bullet_effect(t_eff_list *effect, clock_t time);
void		blow_effect(t_eff_list *effect, clock_t time);

void		alloc_stencil_buf(char ***buf, t_res res);
void		clean_stencil_buf(t_image *img);

#endif