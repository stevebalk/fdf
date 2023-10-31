/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:41:49 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 13:42:33 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_keyhooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, &key_hook, fdf);
	mlx_hook(fdf->win, DestroyNotify,
	StructureNotifyMask, &close_window, fdf);
	mlx_mouse_hook(fdf->win, &mouse_hook, fdf);
	// mlx_loop_hook(fdf->mlx, &party, &fdf);
}
