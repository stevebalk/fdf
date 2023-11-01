/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:28:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/01 14:01:59 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_data *data, t_vec2i pos, int color)
{
	char	*dst;

	if (pos.x < 0 || pos.y < 0 || pos.x >= data->win_size.x
		|| pos.y >= data->win_size.y)
		return ;
	dst = data->addr + (pos.y * data->line_length + pos.x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_hud(t_fdf *fdf, int x, int y, int col)
{
	int	off;

	off = 15;
	mlx_string_put(fdf->mlx, fdf->win, x, y, col, "Move:");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 1, col, "Arrow Keys");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 3, col, "Rotate:");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 4, col, "Z-Axis: Q + E");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 5, col, "X-Axis: A + D");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 6, col, "Y-Axis: S + W");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 8, col, "Zoom:");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 9, col, "Mousewheel");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 11, col, "Change height:");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 12, col, "Numpad + & -");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 13, col, "Projection:");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 14, col, "Iso:  1");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 15, col, "Flat: 2");
}

int	is_line_visible(t_fdf *fdf, t_vec2i start, t_vec2i end)
{
	if ((start.x < 0 && end.x < 0)
		|| (start.x > fdf->win_size.x && end.x > fdf->win_size.x)
		|| (start.y < 0 && end.y < 0)
		|| (start.y > fdf->win_size.y && end.y > fdf->win_size.y))
		return (0);
	return (1);
}
