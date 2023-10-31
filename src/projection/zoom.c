/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:29:00 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/01 00:00:41 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	create_fit_to_window_data(t_fdf *fdf)
{
	int	i;
	int	j;

	j = 0;
	while (j < fdf->map_size.y)
	{
		i = 0;
		while (i < fdf->map_size.x)
		{
			apply_transformations(fdf, &(fdf->input_map[j][i].pos),
				&(fdf->map[j][i].pos));
			i++;
		}
		j++;
	}
}

static void	find_low_high_point(t_fdf *fdf, int *low, int *high)
{
	int	i;
	int	j;
	int	point;

	i = 0;
	while (i < fdf->map_size.y)
	{
		j = 0;
		while (j < fdf->map_size.x)
		{
			point = fdf->map[i][j].pos.y;
			if (point < *low)
				*low = point;
			else if (point > *high)
				*high = point;
			j++;
		}
		i++;
	}
}

float	fit_zoom_to_windowsize(t_fdf *fdf)
{
	int	lowest_point;
	int	highest_point;

	create_fit_to_window_data(fdf);
	lowest_point = fdf->map[0][0].pos.y;
	highest_point = fdf->map[0][0].pos.y;
	find_low_high_point(fdf, &lowest_point, &highest_point);
	if (lowest_point == highest_point)
		return (1);
	return ((float)fdf->win_size.y
		/ ((float)highest_point - lowest_point) * 0.40);
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
