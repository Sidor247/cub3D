/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:54:50 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/30 01:34:35 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	*get_pix_addr(t_image *img, int x, int y)
{
	return ((unsigned *)(img->addr + y * img->line_length
		+ x * (img->bits_per_pixel / 8)));
}

void	update_plane(t_player *player)
{
	float		tmp;

	tmp = tanf(FOV * M_PI / 360);
	player->plane.x = -player->dir.y * tmp;
	player->plane.y = player->dir.x * tmp;
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
