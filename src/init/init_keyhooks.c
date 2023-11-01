/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keyhooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:00:04 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/01 15:41:31 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_keyhooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, DestroyNotify,
		StructureNotifyMask, &close_window, fdf);
	mlx_mouse_hook(fdf->win, &mouse_hook, fdf);
	mlx_hook(fdf->win, KeyPress, KeyPressMask, &key_hook, fdf);
	mlx_loop_hook(fdf->mlx, &autorotate, fdf);
}
