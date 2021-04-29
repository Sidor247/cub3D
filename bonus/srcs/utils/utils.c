/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:54:50 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/26 22:41:50 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

unsigned int	*get_pix_addr(t_image *img, t_point point)
{
	return ((unsigned *)(img->addr + point.y * img->line_length
		+ point.x * (img->bits_per_pixel / 8)));
}

t_vector	get_plane(t_vector dir)
{
	float	tmp;

	tmp = dir.x;
	dir.x = -dir.y;
	dir.y = tmp;
	return (mult_vec(tanf(FOV * M_PI / 360.0), dir));
}

void	none(void *ptr)
{
	ptr++;
}

int	count_digits(char **s)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = *s;
	while (ft_isdigit(*(tmp + i)))
		i++;
	*s = tmp + i;
	return (i);
}

void	show_fps(t_mlx *mlx, clock_t now)
{
	char	s[7];
	int		fps;
	int		i;

	ft_memcpy(s, "fps:", 4);
	s[6] = '\0';
	fps = (int)(CLOCKS_PER_SEC / (now - mlx->data.time));
	i = 5;
	while (i > 3)
	{
		s[i] = (char)(fps % 10) + '0';
		fps /= 10;
		i--;
	}
	mlx_string_put(mlx->ptr, mlx->win, 0, 15, BLACK, s);
}
