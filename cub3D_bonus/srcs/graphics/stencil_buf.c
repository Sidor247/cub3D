/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stencil_buf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:33:09 by cwhis             #+#    #+#             */
/*   Updated: 2021/10/31 17:16:49 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	alloc_stencil_buf(char ***buf, t_res res)
{
	char	**tmp;
	int		i;

	tmp = malloc(res.height * sizeof(char *));
	i = -1;
	while (++i < res.height)
		tmp[i] = malloc(res.width * sizeof(char));
	*buf = tmp;
}

void	clean_stencil_buf(t_image *img)
{
	char	**buf;
	t_res	res;
	int		i;

	i = -1;
	res = img->res;
	buf = img->stencil_buf;
	while (++i < res.height)
		ft_bzero(buf[i], res.width);
}