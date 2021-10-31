/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:39:40 by igorlebedev       #+#    #+#             */
/*   Updated: 2021/10/31 16:58:11 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	write_pixel_data(int fd, t_image *img)
{
	t_point	point;
	int		padding;

	padding = img->res.width * 3 % 4;
	point.y = img->res.height;
	while (point.y--)
	{
		point.x = -1;
		while (++point.x < img->res.width)
			write(fd, get_pix_addr(img, point), 3);
		point.x = -1;
		while (++point.x < padding)
			write(fd, "\0", 1);
	}
}

void	write_le_num(unsigned char *dst, unsigned int num)
{
	*dst = (unsigned char)num;
	*(dst + 1) = (unsigned char)(num >> 8);
	*(dst + 2) = (unsigned char)(num >> 16);
	*(dst + 3) = (unsigned char)(num >> 24);
}

void	create_bmp(t_image *img)
{
	unsigned char	header[54];
	unsigned int	size;
	int				fd;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	size = img->res.width * img->res.height * 3 + 54;
	ft_bzero(header, 54);
	ft_memcpy(header, "BM", 2);
	write_le_num(header + 2, size);
	write_le_num(header + 10, 54);
	write_le_num(header + 14, 40);
	write_le_num(header + 18, img->res.width);
	write_le_num(header + 22, img->res.height);
	header[26] = 1;
	header[28] = 24;
	write(fd, header, 54);
	write_pixel_data(fd, img);
	close(fd);
}
