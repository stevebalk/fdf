/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_canvas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:15:38 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/02 13:10:22 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	toggle_altitude_color(t_fdf *fdf)
{
	int	i;
	int	j;

	fdf->use_alti_colors ^= 1;
	j = 0;
	while (j < fdf->map_size.y)
	{
		i = 0;
		while (i < fdf->map_size.x)
		{
			if (fdf->use_alti_colors)
				fdf->map[j][i].color = fdf->input_map[j][i].alt_color;
			else
				fdf->map[j][i].color = fdf->input_map[j][i].color;
			i++;
		}
		j++;
	}
	update_canvas(fdf);
}

void	apply_transformations(t_fdf *fdf, t_vec3 *src, t_vec2i *dst)
{
	t_vec3	point;

	point.x = src->x;
	point.y = src->y;
	point.z = src->z;
	if (fdf->projection == ISO_PROJECTION)
		project_iso(fdf, &point, dst);
	else if (fdf->projection == TOP_VIEW)
		project_flat(fdf, &point, dst);
	dst->x += fdf->win_center.x + fdf->offset.x;
	dst->y += fdf->win_center.y + fdf->offset.y;
}

void	update_canvas(t_fdf *fdf)
{
	int	i;
	int	j;

	j = 0;
	draw_background(fdf->img, fdf->win_size, fdf->bg_color);
	while (j < fdf->map_size.y)
	{
		i = 0;
		while (i < fdf->map_size.x)
		{
			apply_transformations(fdf, &(fdf->input_map[j][i].pos),
				&(fdf->map[j][i].pos));
			i++;
		}
		j++;
	}
	draw_mesh(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	draw_hud(fdf, 20, 30, WHITE);
}
