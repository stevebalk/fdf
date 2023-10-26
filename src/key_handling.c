/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:35:44 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/26 16:06:26 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
	{
		free_everything(fdf);
		exit(EXIT_SUCCESS);
	}
	if (keycode == XK_Left)
		fdf->angle.z = fdf->rotation_angle;
	if (keycode == XK_Right)
		fdf->angle.z = -fdf->rotation_angle;
	if (fdf)
		printf("Keycode: %d\n", keycode);
	if (keycode == XK_w)
		fdf->offset.y -= 50;
	if (keycode == XK_s)
		fdf->offset.y += 50;
	if (keycode == XK_a)
		fdf->offset.x -= 50;
	if (keycode == XK_d)
		fdf->offset.x += 50;
	rotate(fdf);
	project_iso(fdf);
	transform(fdf, fdf->offset);
	draw_background(fdf->img, fdf->win_size, fdf->bg_color);
	draw_mesh(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_fdf *fdf)
{
	x += 1;
	y += 1;
	if (fdf)
		printf("Keycode(Mouse): %d\n", keycode);
	if (keycode == MOUSE_WHEEL_UP || keycode == MOUSE_WHEEL_DOWN)
		zoom(fdf, keycode);
	project_iso(fdf);
	transform(fdf, fdf->offset);
	draw_background(fdf->img, fdf->win_size, fdf->bg_color);
	draw_mesh(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	return (0);
}
