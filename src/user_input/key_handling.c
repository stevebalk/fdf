/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:35:44 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/07 10:52:24 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		close_window(fdf, 0);
	if (keycode == XK_x)
		fdf->autorotate.x ^= 1;
	if (keycode == XK_y)
		fdf->autorotate.y ^= 1;
	if (keycode == XK_z)
		fdf->autorotate.z ^= 1;
	if (keycode == XK_h)
		toggle_altitude_color(fdf);
	if (movement_keys_pressed(keycode, fdf)
		|| rotation_keys_pressed(keycode, fdf)
		|| height_keys_pressed(keycode, fdf)
		|| projection_keys_pressed(keycode, fdf))
		update_canvas(fdf);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_fdf *fdf)
{
	(void) x;
	(void) y;
	if (zoom_keys_pressed(keycode, fdf))
		update_canvas(fdf);
	return (0);
}
