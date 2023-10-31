/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:35:44 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 15:04:27 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	movement_keys_pressed(int keycode, t_fdf *fdf)
{
	int pressed;

	pressed = 0;
	if (keycode == XK_w)
		pressed = change_offset(&fdf->offset.y, -OFFSET_STEP);
	if (keycode == XK_s)
		pressed = change_offset(&fdf->offset.y, OFFSET_STEP);
	if (keycode == XK_a)
		pressed = change_offset(&fdf->offset.x, -OFFSET_STEP);
	if (keycode == XK_d)
		pressed = change_offset(&fdf->offset.x, OFFSET_STEP);
	return (pressed);
}

int	rotation_keys_pressed(int keycode, t_fdf *fdf)
{
	int		pressed;

	pressed = 0;
	if (keycode == XK_Left)
		pressed = change_rotation(&fdf->angle.z, ROTATION_STEP);
	if (keycode == XK_Right)
		pressed = change_rotation(&fdf->angle.z, -ROTATION_STEP);
	if (keycode == XK_Up)
		pressed = change_rotation(&fdf->angle.x, ROTATION_STEP);
	if (keycode == XK_Down)
		pressed = change_rotation(&fdf->angle.x, -ROTATION_STEP);
	if (keycode == XK_k)
		pressed = change_rotation(&fdf->angle.y, ROTATION_STEP);
	if (keycode == XK_l)
		pressed = change_rotation(&fdf->angle.y, -ROTATION_STEP);
	return (pressed);
}

int	height_keys_pressed(int keycode, t_fdf *fdf)
{
	int	pressed;

	pressed = 0;
	if (keycode == XK_KP_Add)
		pressed = change_height(fdf, HEIGHT_STEP);
	if (keycode == XK_KP_Subtract)
		pressed = change_height(fdf, -HEIGHT_STEP);
	return (pressed);
}

int	zoom_keys_pressed(int keycode, t_fdf *fdf)
{
	int	pressed;

	pressed = 0;
	if (keycode == MOUSE_WHEEL_UP)
		pressed = zoom_in(fdf, ZOOM_MOD);
	if (keycode == MOUSE_WHEEL_DOWN)
		pressed = zoom_out(fdf, ZOOM_MOD);
	return (pressed);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		close_window(fdf);
	if (movement_keys_pressed(keycode, fdf)
	|| rotation_keys_pressed(keycode, fdf)
	|| height_keys_pressed(keycode, fdf))
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
