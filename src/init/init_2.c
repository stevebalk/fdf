/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:41:49 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 21:32:39 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_keyhooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, DestroyNotify,
		StructureNotifyMask, &close_window, fdf);
	mlx_mouse_hook(fdf->win, &mouse_hook, fdf);
	mlx_hook(fdf->win, KeyPress, KeyPressMask, &key_hook, fdf);
}

int	init_iso_projection(t_fdf *fdf)
{
	fdf->angle.x = 0;
	fdf->angle.y = 0;
	fdf->zoom = 1;
	fdf->angle.z = deg_to_rad(-90);
	update_canvas(fdf);
	fdf->zoom = fit_zoom_to_windowsize(fdf);
	return (1);
}

int	init_flat_projection(t_fdf *fdf)
{
	fdf->angle.x = 0;
	fdf->angle.y = 0;
	fdf->angle.z = 0;
	fdf->zoom = 1;
	update_canvas(fdf);
	fdf->zoom = fit_zoom_to_windowsize(fdf);
	return (1);
}
