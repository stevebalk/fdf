/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:45:02 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/02 13:16:37 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 14, col, "Projection:");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 15, col, "Iso:  1");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 16, col, "Flat: 2");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 18, col, "Autorotate:");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 19, col, "x + y + z");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 21, col, "Use alt color");
	mlx_string_put(fdf->mlx, fdf->win, x, y + off * 22, col, "h");
}
