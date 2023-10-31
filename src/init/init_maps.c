/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:58:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 21:59:35 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_input_map(t_fdf *fdf)
{
	int	i;

	if (fdf->map_size.x > 0 && fdf->map_size.y > 0)
	{
		i = 0;
		fdf->input_map = ft_calloc(fdf->map_size.y + 1, sizeof(t_vert3d *));
		if (fdf->input_map == NULL)
			error_msg(fdf, "Error: ft_calloc failed", 1, 1);
		while (i < fdf->map_size.y)
		{
			fdf->input_map[i] = calloc(fdf->map_size.x + 1, sizeof(t_vert3d));
			if (fdf->input_map[i] == NULL)
				error_msg(fdf, "Error: ft_calloc failed", 1, 1);
			i++;
		}
	}
	else
		error_msg(fdf, "Error: Init_input_map: Map size to small", 0, 1);
}

static void	init_map(t_fdf *fdf)
{
	int	i;

	if (fdf->map_size.x > 0 && fdf->map_size.y > 0)
	{
		i = 0;
		fdf->map = ft_calloc(fdf->map_size.y + 1, sizeof(t_vert2d *));
		if (fdf->input_map == NULL)
			error_msg(fdf, "Error: ft_calloc failed", 1, 1);
		while (i < fdf->map_size.y)
		{
			fdf->map[i] = calloc(fdf->map_size.x + 1, sizeof(t_vert2d));
			if (fdf->map[i] == NULL)
				error_msg(fdf, "Error: ft_calloc failed", 1, 1);
			i++;
		}
	}
	else
		error_msg(fdf, "Error: init_map: Map size to small", 0, 1);
}

void	init_maps(t_fdf *fdf)
{
	fdf->pivot.x = ((float)fdf->map_size.x - 1) / 2;
	fdf->pivot.y = ((float)fdf->map_size.y - 1) / 2;
	init_input_map(fdf);
	init_map(fdf);
}
