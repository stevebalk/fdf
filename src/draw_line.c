/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:18:40 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/29 16:52:20 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Return 1 if point is inside window, 0 if not */
int	is_point_in_window(t_fdf *fdf, t_vec2i point)
{
	if ((point.x >= 0 && point.x < fdf->win_size.x)
		&& (point.y >= 0 && point.y < fdf->win_size.y))
		return (1);
	return (0);
}

/*Checks if line would be visible */
int	is_line_visible(t_fdf *fdf, t_vec2i start, t_vec2i end)
{
	if (is_point_in_window(fdf, start))
		return (1);
	if (is_point_in_window(fdf, end))
		return (1);
	return (0);
}

/* Sets next point, returns 1 if successful, 0 if not*/
int	get_next_point(t_line *line, t_vec2i *start, t_vec2i end)
{
	if (start->x == end.x && start->y == end.y)
			return(0) ;
	line->err2 = 2 * line->err;
	if (line->err2 >= line->dy)
	{
		line->err += line->dy;
		start->x += line->sx;
	}
	if (line->err2 <= line->dx)
	{
		line->err += line->dx;
		start->y += line->sy;
	}
	return (1);
}

// int is_line_visible(t_fdf *fdf, t_vec2i start, t_vec2i end)
// {
// 	t_line	line;

// 	line.dx = abs(end.x - start.x);
// 	line.sx = ft_sign(start.x - end.x) * -1;
// 	line.dy = -abs(end.y - start.y);
// 	line.sy = ft_sign(start.y - end.y) * -1;
// 	line.err = line.dx + line.dy;

// 	if (is_point_in_window(fdf, start))
// 		return 1;
// 	while (get_next_point(&line, &start, end))
// 		if (is_point_in_window(fdf, start))
// 			return 1;
// 	return 0;
// }

/* Bresenham's algorithm */
void	draw_line(t_fdf *fdf, t_vec2i start, t_vec2i end, int color)
{
	t_line	line;

	line.dx = abs(end.x - start.x);
	line.sx = ft_sign(start.x - end.x) * -1;
	line.dy = -abs(end.y - start.y);
	line.sy = ft_sign(start.y - end.y) * -1;
	line.err = line.dx + line.dy;
	my_mlx_pixel_put(fdf->img, start, color);
	while (get_next_point(&line, &start, end))
		my_mlx_pixel_put(fdf->img, start, color);
}

// void	draw_line(t_fdf *fdf, t_vec2i start, t_vec2i end, int color)
// {
// 	if (is_line_visible(fdf, start, end))
// 		line_draw_algoritm(fdf, start, end, color);
// }
