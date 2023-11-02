/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   altitude_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:33:21 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/02 13:44:14 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_highest_altitude(t_fdf *fdf)
{
	int	highest_altitude;
	int	i;
	int	j;

	highest_altitude = fdf->input_map[0][0].pos.z;
	i = 0;
	while (i < fdf->map_size.x)
	{
		j = 0;
		while (j < fdf->map_size.y)
		{
			if (fdf->input_map[j][i].pos.z > highest_altitude)
				highest_altitude = fdf->input_map[j][i].pos.z;
			j++;
		}
		i++;
	}
	return (highest_altitude);
}

static void	set_point_color(t_vert3d *vert, int highest)
{
	int	percentage;

	percentage = round(100.0 / highest * vert->pos.z);
	if (percentage < -10)
		vert->alt_color = DARK_BLUE;
	else if (percentage <= 0)
		vert->alt_color = BLUE;
	else if (percentage < 5)
		vert->alt_color = 0x9B9B63;
	else if (percentage < 10)
		vert->alt_color = 0xAAAA55;
	else if (percentage < 15)
		vert->alt_color = 0xC6C638;
	else if (percentage < 20)
		vert->alt_color = 0xD4D42A;
	else if (percentage < 30)
		vert->alt_color = 0xE2E21C;
	else if (percentage < 40)
		vert->alt_color = YELLOW;
	else if (percentage < 50)
		vert->alt_color = LIGHT_GREY;
	else
		vert->alt_color = WHITE;
}

/* Calculate and set altitude color for every point */
void	set_altitude_color(t_fdf *fdf)
{
	int	highest_altitude;
	int	i;
	int	j;

	highest_altitude = get_highest_altitude(fdf);
	i = 0;
	while (i < fdf->map_size.x)
	{
		j = 0;
		while (j < fdf->map_size.y)
		{
			set_point_color(&fdf->input_map[j][i], highest_altitude);
			j++;
		}
		i++;
	}
}
