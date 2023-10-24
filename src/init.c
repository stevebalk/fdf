/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:35:08 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/24 13:49:12 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_input_map(t_fdf *fdf)
{
	int	i;
	ft_printf("Mapsize: x: %i, y: %i\n", fdf->map_size.x, fdf->map_size.y);

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

void	init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF");
	fdf->input_map = NULL;
	fdf->map = NULL;
	fdf->map_size = (t_vec2){0, 0};
	fdf->win_size.x = WIDTH;
	fdf->win_size.y = HEIGHT;
	fdf->bg_color = BLACK;
	fdf->default_color = WHITE;
	fdf->cur_color = fdf->default_color;
	fdf->zoom = 20;
}

void	init_maps(t_fdf *fdf)
{
	init_input_map(fdf);
	init_map(fdf);
}