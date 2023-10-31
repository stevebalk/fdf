/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:35:08 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 22:01:46 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_fdf(t_fdf *fdf)
{
	fdf->input_map = NULL;
	fdf->mlx = NULL;
	fdf->map = NULL;
	fdf->img = NULL;
	fdf->map_size = (t_vec2i){0, 0};
	fdf->win_size.x = WIDTH;
	fdf->win_size.y = HEIGHT;
	fdf->bg_color = 0x19;
	fdf->default_color = DEFAULT_COLOR;
	fdf->zoom = 1;
	fdf->angle = (t_vec3){0.0, 0.0, 0.0};
	fdf->win_center = (t_vec2i){fdf->win_size.x / 2, fdf->win_size.y / 2};
	fdf->offset = (t_vec2i){0, 0};
	fdf->projection = 1;
}
