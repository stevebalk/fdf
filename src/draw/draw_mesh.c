/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:08:50 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/01 16:40:44 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_mesh_edge(t_fdf *fdf, t_vert2d *start, t_vert2d *end)
{
	if (is_line_visible(fdf, start->pos, end->pos))
	{
		if (start->color != end->color)
			draw_line_gradient(fdf, *start, *end);
		else
			draw_line(fdf, start->pos, end->pos, start->color);
	}
}

/* Draw the mesh based on fdf->map */
void	draw_mesh(t_fdf *fdf)
{
	int	x;
	int	y;

	x = 0;
	while (x < fdf->map_size.y)
	{
		y = 0;
		while (y < fdf->map_size.x)
		{
			if (x != 0)
				draw_mesh_edge(fdf, &fdf->map[x][y], &fdf->map[x - 1][y]);
			if (y != 0)
				draw_mesh_edge(fdf, &fdf->map[x][y], &fdf->map[x][y - 1]);
			y++;
		}
		x++;
	}
}
