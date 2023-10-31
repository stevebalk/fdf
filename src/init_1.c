/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:35:08 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 14:18:18 by sbalk            ###   ########.fr       */
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

void	init_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		error_msg(fdf, "Error: mlx_init failed", 1, 1);
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF");
	if (fdf->win == NULL)
		error_msg(fdf, "Error: mlx_new_window failed", 1, 1);
	fdf->img = ft_calloc(1, sizeof(t_data));
	if (fdf->img == NULL)
		error_msg(fdf, "Error: init_mlx ft_calloc failed", 1, 1);
	fdf->img->img = mlx_new_image(fdf->mlx, fdf->win_size.x, fdf->win_size.y);
	if (fdf->img->img == NULL)
		error_msg(fdf, "Error: mlx_new_image failed", 0, 1);
	fdf->img->addr = mlx_get_data_addr(fdf->img->img,
			&(fdf->img->bits_per_pixel),
			&(fdf->img->line_length), &(fdf->img->endian));
	fdf->img->win_size = fdf->win_size;
	printf("Line length: %d\n", fdf->img->line_length / 4);
}

void	init_fdf(t_fdf *fdf)
{
	fdf->input_map = NULL;
	fdf->mlx = NULL;
	fdf->map = NULL;
	fdf->img = NULL;
	fdf->map_size = (t_vec2i){0, 0};
	fdf->win_size.x = WIDTH;
	fdf->win_size.y = HEIGHT;
	fdf->bg_color = 0x19;
	fdf->default_color = DEFAULT_COLOR;
	fdf->zoom = 1;
	fdf->angle = (t_vec3){0.0, 0.0, 0.0};
	fdf->win_center = (t_vec2i) {fdf->win_size.x / 2, fdf->win_size.y / 2};
	fdf->offset = (t_vec2i){0, 0};
}

void	init_maps(t_fdf *fdf)
{
	fdf->pivot.x = ((float)fdf->map_size.x - 1) / 2;
	fdf->pivot.y = ((float)fdf->map_size.y - 1) / 2;
	init_input_map(fdf);
	init_map(fdf);
}
