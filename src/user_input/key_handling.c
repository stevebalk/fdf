/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:35:44 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/01 15:40:17 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		close_window(fdf);
	if (keycode == XK_x)
		fdf->autorotate.x = ~fdf->autorotate.x;
	if (keycode == XK_y)
		fdf->autorotate.y = ~fdf->autorotate.y;
	if (keycode == XK_z)
		fdf->autorotate.z = ~fdf->autorotate.z;
	if (movement_keys_pressed(keycode, fdf)
		|| rotation_keys_pressed(keycode, fdf)
		|| height_keys_pressed(keycode, fdf)
		|| projection_keys_pressed(keycode, fdf))
		update_canvas(fdf);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_fdf *fdf)
{
	x = x;
	y = y;
	if (zoom_keys_pressed(keycode, fdf))
		update_canvas(fdf);
	return (0);
}
