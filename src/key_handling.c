/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:35:44 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/02 18:28:28 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zoom(int key, t_fdf *fdf)
{
	printf("PEWPEPEWPEWPE\n");
	if (key == MOUSE_CLICK_LEFT)
		{
			fdf->zoom += 1;
			// redraw(fdf);
			printf("Zoom = %p\n", &fdf);
			printf("ZOOM IN\n");
			fflush(stdout);
		}
		if (key == MOUSE_WHEEL_DOWN)
		{
			fdf->zoom -= 1;
			// redraw(fdf);
			printf("ZOOM OUT\n");
			fflush(stdout);
		}
}

void mouse_click(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	printf("PEWPEPEWPEWPE\n");
	if (key == MOUSE_CLICK_LEFT || MOUSE_WHEEL_DOWN)
		zoom(key, fdf);
}

void	setup_controls(t_fdf *fdf)
{
	mlx_hook(fdf->win, 4, 0, mouse_click, fdf);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		exit(0);
	if (vars)
		printf("Keycode: %d\n", keycode);
	return (0);
}

int mouse_hook(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	if (fdf)
	{
		if (keycode == MOUSE_WHEEL_UP)
		{
			fdf->zoom += 1;
			// redraw(fdf);
			// printf("Zoom = %p\n", &fdf);
			printf("ZOOM IN\n");
			fflush(stdout);
		}
		if (keycode == MOUSE_WHEEL_DOWN)
		{
			// fdf->zoom -= 1;
			// redraw(fdf);
			printf("ZOOM OUT\n");
			fflush(stdout);
		}
	}
	return (0);
}