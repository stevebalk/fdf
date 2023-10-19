/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:35:08 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/11 16:18:21 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF");
	fdf->input_map = NULL;
	fdf->map = NULL;
	fdf->map_size = (t_vec2){0, 0};
	fdf->win_size.x = WIDTH;
	fdf->win_size.y = HEIGHT;
	fdf->bg_color	= BLACK;
	fdf->default_color = WHITE;
	fdf->cur_color = fdf->default_color;
	fdf->zoom = 50;
}