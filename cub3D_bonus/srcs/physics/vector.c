/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 22:59:39 by cwhis             #+#    #+#             */
/*   Updated: 2021/10/30 02:30:46 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_vector	add_vec(t_vector a, t_vector b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

t_vector	mult_vec(float k, t_vector vec)
{
	vec.x *= k;
	vec.y *= k;
	return (vec);
}

t_vector	sub_vec(t_vector a, t_vector b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

t_vector	vector(float x, float y)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}
