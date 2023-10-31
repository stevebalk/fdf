/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:29:00 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 21:24:20 by sbalk            ###   ########.fr       */
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

	lowest_point = fdf->map[0][0].pos.y;
	highest_point = fdf->map[0][0].pos.y;
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
	return ((float)fdf->win_size.y
		/ ((float)highest_point - lowest_point) * 0.50);
}

int	zoom_in(t_fdf *fdf, float value)
{
	if (fdf->zoom < ZOOM_MAX)
	{
		fdf->offset.x *= value;
		fdf->offset.y *= value;
		fdf->zoom *= value;
		return (1);
	}
	return (0);
}

int	zoom_out(t_fdf *fdf, float value)
{
	if (fdf->zoom > ZOOM_MIN)
	{
		fdf->offset.x /= value;
		fdf->offset.y /= value;
		fdf->zoom /= value;
		return (1);
	}
	return (0);
}
