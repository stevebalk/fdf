/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:29:00 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/25 14:31:50 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	fit_zoom_to_windowsize(t_fdf *fdf)
{
	int	smallest_point;
	int	highest_point;
	int	point;
	int	i;
	int	j;

	smallest_point = 0;
	highest_point = 0;
	i = 0;
	while (i < fdf->map_size.y)
	{
		j = 0;
		while (j < fdf->map_size.x)
		{
			point = fdf->map[i][j].pos.y;
			if (point < smallest_point)
				smallest_point = point;
			else if (point > highest_point)
				highest_point = point;
			j++;
		}
		i++;
	}
	return ((float)fdf->win_size.y / (fdf->map_size.y
			+ highest_point - smallest_point));
}

void	zoom(t_fdf *fdf, int zoom)
{
	int	i;
	int	j;

	if (zoom > 0)
	{
		i = 0;
		while (i < fdf->map_size.x)
		{
			j = 0;
			while (j < fdf->map_size.y)
			{
				fdf->map[j][i].pos.x *= zoom;
				fdf->map[j][i].pos.y *= zoom;
				j++;
			}
			i++;
		}
	}
}
