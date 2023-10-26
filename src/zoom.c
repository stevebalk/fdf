/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:29:00 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/26 15:57:59 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	fit_zoom_to_windowsize(t_fdf *fdf)
{
	int	lowest_point;
	int	highest_point;
	int	point;
	int	i;
	int	j;

	lowest_point = 0;
	highest_point = 0;
	i = 0;
	while (i < fdf->map_size.y)
	{
		j = 0;
		while (j < fdf->map_size.x)
		{
			point = fdf->map[i][j].pos.y;
			if (point < lowest_point)
				lowest_point = point;
			else if (point > highest_point)
				highest_point = point;
			j++;
		}
		i++;
	}
	printf("Pivot.y = %f\n", fdf->pivot.y);
	printf("Lowest Point = %i\n", highest_point);
	return ((float)fdf->win_size.y / ((float)highest_point - lowest_point + highest_point) * 0.50);
}

void	zoom(t_fdf *fdf, int keycode)
{
	if (keycode == MOUSE_WHEEL_UP)
	{
		if (fdf->zoom < fdf->max_zoom)
		{
			fdf->offset.x *= fdf->zoom_mod;
			fdf->offset.y *= fdf->zoom_mod;
			fdf->zoom *= fdf->zoom_mod;
		}
	}
	if (keycode == MOUSE_WHEEL_DOWN)
	{
		if (fdf->zoom > fdf->min_zoom)
		{
			fdf->offset.x /= fdf->zoom_mod;
			fdf->offset.y /= fdf->zoom_mod;
			fdf->zoom /= fdf->zoom_mod;
		}
	}
}
