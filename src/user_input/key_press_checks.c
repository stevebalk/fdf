/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:27:14 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/02 11:53:02 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	movement_keys_pressed(int keycode, t_fdf *fdf)
{
	int	pressed;

	pressed = 0;
	if (keycode == XK_Up)
		pressed = change_offset(&fdf->offset.y, -OFFSET_STEP);
	if (keycode == XK_Down)
		pressed = change_offset(&fdf->offset.y, OFFSET_STEP);
	if (keycode == XK_Left)
		pressed = change_offset(&fdf->offset.x, -OFFSET_STEP);
	if (keycode == XK_Right)
		pressed = change_offset(&fdf->offset.x, OFFSET_STEP);
	return (pressed);
}

int	rotation_keys_pressed(int keycode, t_fdf *fdf)
{
	int		pressed;

	pressed = 0;
	if (keycode == XK_q)
		pressed = change_rotation(&fdf->angle.z, ROTATION_STEP);
	if (keycode == XK_e)
		pressed = change_rotation(&fdf->angle.z, -ROTATION_STEP);
	if (keycode == XK_a)
		pressed = change_rotation(&fdf->angle.x, ROTATION_STEP);
	if (keycode == XK_d)
		pressed = change_rotation(&fdf->angle.x, -ROTATION_STEP);
	if (keycode == XK_s)
		pressed = change_rotation(&fdf->angle.y, ROTATION_STEP);
	if (keycode == XK_w)
		pressed = change_rotation(&fdf->angle.y, -ROTATION_STEP);
	return (pressed);
}

int	height_keys_pressed(int keycode, t_fdf *fdf)
{
	int	pressed;

	pressed = 0;
	if (keycode == XK_KP_Add)
		pressed = change_height(fdf, 1.1);
	if (keycode == XK_KP_Subtract)
		pressed = change_height(fdf, 0.9);
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

int	projection_keys_pressed(int keycode, t_fdf *fdf)
{
	int	pressed;

	pressed = 0;
	if (keycode == XK_1 && fdf->projection != ISO_PROJECTION)
	{
		pressed = init_iso_projection(fdf);
		fdf->projection = ISO_PROJECTION;
	}
	else if (keycode == XK_2 && fdf->projection != TOP_VIEW)
	{
		pressed = init_flat_projection(fdf);
		fdf->projection = TOP_VIEW;
	}
	return (pressed);
}
