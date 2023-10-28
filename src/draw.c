/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:28:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/27 16:40:00 by sbalk            ###   ########.fr       */
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

/* Bresenham's algorithm */
void	line_draw_algoritm(t_fdf *fdf, t_vec2i start, t_vec2i end, int color)
{
	t_line	line;
	int		e2;

	line.dx = ft_abs(end.x - start.x);
	line.sx = ft_sign(start.x - end.x) * -1;
	line.dy = -abs(end.y - start.y);
	line.sy = ft_sign(start.y - end.y) * -1;
	line.err = line.dx + line.dy;
	while (1)
	{
		my_mlx_pixel_put(fdf->img, start, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * line.err;
		if (e2 >= line.dy)
		{
			line.err += line.dy;
			start.x += line.sx;
		}
		if (e2 <= line.dx)
		{
			line.err += line.dx;
			start.y += line.sy;
		}
	}
}

int	is_point_in_window(t_fdf *fdf, t_vec2i point)
{
	if ((point.x >= 0 && point.x < fdf->win_size.x)
		|| (point.y >= 0 && point.y < fdf->win_size.y))
		return (1);
	return (0);
}

int	is_line_visible(t_fdf *fdf, t_vec2i start, t_vec2i end)
{
	if (is_point_in_window(fdf, start))
		return (1);
	if (is_point_in_window(fdf, end))
		return (1);
	return (0);
}

void	draw_line(t_fdf *fdf, t_vec2i start, t_vec2i end, int color)
{
	if (is_line_visible(fdf, start, end))
		line_draw_algoritm(fdf, start, end, color);
}


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
				draw_line(fdf, fdf->map[x][y].pos,
					fdf->map[x - 1][y].pos, fdf->input_map[x][y].color);
			if (y != 0)
				draw_line(fdf, fdf->map[x][y].pos,
					fdf->map[x][y - 1].pos, fdf->input_map[x][y].color);
			y++;
		}
		x++;
	}
}
