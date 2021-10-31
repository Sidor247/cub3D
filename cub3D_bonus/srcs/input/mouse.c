/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 02:34:37 by cwhis             #+#    #+#             */
/*   Updated: 2021/10/30 02:30:08 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mouse_grab(int *mouse)
{
	if (MOUSE)
	{
		mlx_mouse_hide();
		*mouse |= 0x8000;
	}
	return (1);
}

int	mouse_free(int *mouse)
{
	mlx_mouse_show();
	*mouse &= ~0x8000;
	return (1);
}

int	button_press(int button, int x, int y, int *mouse)
{
	if (*mouse & 0x8000)
	{
		if (button == BUTTON_1)
			*mouse |= 0x01;
		else if (button == BUTTON_2)
			*mouse |= 0x02;
		else if (button == BUTTON_3)
			*mouse |= 0x04;
		else if (button == BUTTON_4)
			*mouse |= 0x08;
		else if (button == BUTTON_5)
			*mouse |= 0x10;
	}
	else
		mouse_grab(mouse);
	x++;
	y++;
	return (1);
}

int	button_release(int button, int x, int y, int *mouse)
{
	if (button == BUTTON_1)
		*mouse &= ~0x01;
	else if (button == BUTTON_2)
		*mouse &= ~0x02;
	else if (button == BUTTON_3)
		*mouse &= ~0x04;
	else if (button == BUTTON_4)
		*mouse &= ~0x08;
	else if (button == BUTTON_5)
		*mouse &= ~0x10;
	x++;
	y++;
	return (1);
}
