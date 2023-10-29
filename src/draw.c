/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:28:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/29 12:40:28 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, t_vec2i pos, int color)
{
	char	*dst;

	if (pos.x < 0 || pos.y < 0 || pos.x >= data->win_size.x
		|| pos.y >= data->win_size.y)
		return ;
	dst = data->addr + (pos.y * data->line_length + pos.x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_data *data, t_vec2i start, t_vec2i end, int color)
{
	int	y_start;

	y_start = start.y;
	while (start.x < end.x)
	{
		start.y = y_start;
		while (start.y < end.y)
		{
			my_mlx_pixel_put(data, start, color);
			start.y++;
		}
		start.x++;
	}
}

void	draw_background(t_data *data, t_vec2i size, int color)
{
	t_vec2i	start;

	start.x = 0;
	start.y = 0;
	draw_rect(data, start, size, color);
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
			{
				// if (fdf->map[x][y].color != fdf->map[x - 1][y].color)
				// 	draw_line_gradient(fdf, fdf->map[x][y], fdf->map[x - 1][y]);
				// else
					draw_line(fdf, fdf->map[x][y].pos,
						fdf->map[x - 1][y].pos, fdf->input_map[x][y].color);

			}
			if (y != 0)
			{
				// if (fdf->map[x][y].color != fdf->map[x][y - 1].color)
				// 	draw_line_gradient(fdf, fdf->map[x][y], fdf->map[x][y - 1]);
				// else
					draw_line(fdf, fdf->map[x][y].pos,
						fdf->map[x][y - 1].pos, fdf->input_map[x][y].color);
			}
			y++;
		}
		x++;
	}
}
