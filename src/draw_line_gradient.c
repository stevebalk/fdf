/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_gradient.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:28:22 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/29 16:49:30 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Interpolate single component */
int	interpolate_component(int start, int end, float t)
{
	return (start + (int)((end - start) * t));
}

/* Interpolate color for every channel */
int	interpolate_color(int startColor, int endColor, float t)
{
	t_rgb	start;
	t_rgb	end;
	t_rgb	interpolated;

	start.r = (startColor >> 16) & 0xFF;
	start.g = (startColor >> 8) & 0xFF;
	start.b = startColor & 0xFF;
	end.r = (endColor >> 16) & 0xFF;
	end.g = (endColor >> 8) & 0xFF;
	end.b = endColor & 0xFF;
	interpolated.r = interpolate_component(start.r, end.r, t);
	interpolated.g = interpolate_component(start.g, end.g, t);
	interpolated.b = interpolate_component(start.b, end.b, t);
	return ((interpolated.r << 16) | (interpolated.g << 8) | interpolated.b);
}

/* Returns the color for the current point in a gradient line*/
int	next_gradient_col(int s_col, int e_col, int step, int steps)
{
	float	t;
	int		current_color;

	t = (float) step / steps;
	current_color = interpolate_color(s_col, e_col, t);
	return (current_color);
}

/* Draw a gradient line from start to end */
void	draw_line_gradient(t_fdf *fdf, t_vert2d start, t_vert2d end)
{
	t_line	line;
	int		i;
	int		steps;

	i = 0;
	steps = fmax(abs(end.pos.x - start.pos.x), abs(end.pos.y - start.pos.y));
	line.dx = ft_abs(end.pos.x - start.pos.x);
	line.sx = ft_sign(start.pos.x - end.pos.x) * -1;
	line.dy = -abs(end.pos.y - start.pos.y);
	line.sy = ft_sign(start.pos.y - end.pos.y) * -1;
	line.err = line.dx + line.dy;
	my_mlx_pixel_put(fdf->img, start.pos, next_gradient_col(start.color,
			end.color, i, steps));
	while (get_next_point(&line, &start.pos, end.pos))
	{
		my_mlx_pixel_put(fdf->img, start.pos, next_gradient_col(start.color,
				end.color, i, steps));
		i++;
	}
}
