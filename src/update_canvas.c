/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_canvas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:15:38 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/29 18:16:13 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	apply_transformations(t_fdf *fdf, t_vec3 *src, t_vec2i *dst)
{
	rotate_z(src, fdf->angle.z);
	rotate_x(src, fdf->angle.x);
	rotate_y(src, fdf->angle.y);
	dst->x = ft_round(((src->x - src->y) * cos(0.523599)) * fdf->zoom);
	dst->y = ft_round((-src->z + (src->x + src->y) * sin(0.523599)) * fdf->zoom);
	// dst->x = ft_round((src->x - src->y) * 0.999958244);
	// dst->y = ft_round(-src->z + (src->x + src->y) * 0.009138399);
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
			apply_transformations(fdf, &(fdf->input_map[j][i].pos), &(fdf->map[j][i].pos));
			i++;
		}
		j++;
	}
	draw_mesh(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	fdf->angle.x = 0;
	fdf->angle.y = 0;
	fdf->angle.z = 0;
	// transform(fdf, fdf->offset);
}
