/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:50:20 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/17 19:05:26 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	parser(t_mlx *mlx, char *file)
{
	t_list	*lines;
	t_list	*tmp;
	int		code;

	if (file_to_list(&lines, file))
		mlx_error(mlx, 0);
	tmp = lines;
	while (tmp)
	{
		code = parse_and_trim(mlx, tmp->content);
		if (code != 1)
			break ;
		tmp = tmp->next;
	}
	if (code == 2)
		code = parse_map(&mlx->data, lines, tmp);
	ft_lstclear(&lines, free);
	if (code != 2)
		mlx_error(mlx, code);
}

int	parse_something(t_mlx *mlx, char *s)
{
	if (ft_strnstr(s, "R ", 2))
		return (parse_res(mlx->ptr, &mlx->data.res, s + 2));
	else if (ft_strnstr(s, "NO ", 3))
		return (parse_tex(mlx->ptr, &mlx->data.textures[0], s + 3));
	else if (ft_strnstr(s, "SO ", 3))
		return (parse_tex(mlx->ptr, &mlx->data.textures[1], s + 3));
	else if (ft_strnstr(s, "WE ", 3))
		return (parse_tex(mlx->ptr, &mlx->data.textures[2], s + 3));
	else if (ft_strnstr(s, "EA ", 3))
		return (parse_tex(mlx->ptr, &mlx->data.textures[3], s + 3));
	else if (ft_strnstr(s, "S ", 2))
		return (parse_tex(mlx->ptr, &mlx->data.textures[4], s + 2));
	else if (ft_strnstr(s, "C ", 2))
		return (parse_color(&mlx->data.c_color, s + 2));
	else if (ft_strnstr(s, "F ", 2))
		return (parse_color(&mlx->data.f_color, s + 2));
	else if (ft_strchr("012NSWE", *s))
		return (2);
	return (-4);
}

int	parse_res(void *mlx_ptr, t_res *res, char *s)
{
	int		dig_count;
	int		a[2];
	int		i;

	if (res->width != -1 || res->height != -1)
		return (-3);
	i = -1;
	while (++i < 2)
	{
		while (*s == ' ')
			s++;
		a[i] = ft_atoi(s);
		dig_count = 0;
		dig_count = count_digits(&s);
		if (dig_count > 9)
			return (-5);
	}
	if (a[0] < 1 || a[1] < 1 || *s)
		return (-5);
	mlx_get_screen_size(mlx_ptr, &res->width, &res->height);
	if (a[0] < res->width)
		res->width = a[0];
	if (a[1] < res->height)
		res->height = a[1];
	return (1);
}

int	parse_color(unsigned int *color, char *s)
{
	unsigned int	arr[3];
	int				dig;
	int				commas;
	int				i;

	if (*color != 0xFF000000)
		return (-3);
	commas = 0;
	i = -1;
	while (++i < 3)
	{
		dig = 0;
		s--;
		while (*(++s) == ' ' || *s == ',')
			if (*s == ',')
				commas++;
		arr[i] = ft_atoi(s);
		dig = count_digits(&s);
		if (arr[i] > 255 || arr[i] < 0 || dig < 1 || dig > 3)
			return (-7);
	}
	if (commas != 2 || *s)
		return (-7);
	*color = 0 << 24 | arr[0] << 16 | arr[1] << 8 | arr[2];
	return (1);
}

int	parse_tex(void *mlx_ptr, t_image *img, char *s)
{
	if (img->ptr != NULL)
		return (-3);
	while (*s == ' ')
		s++;
	if (check_extension(s, ".xpm"))
		img->ptr = mlx_xpm_file_to_image(mlx_ptr, s,
				&img->res.width, &img->res.height);
	else if (check_extension(s, ".png"))
		img->ptr = mlx_png_file_to_image(mlx_ptr, s,
				&img->res.width, &img->res.height);
	if (img->ptr == NULL)
		return (-6);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (1);
}
