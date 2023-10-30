/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:41:41 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/30 15:27:18 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "fdf.h"

void	print_input_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < fdf->map_size.y)
	{
		while (j < fdf->map_size.x)
		{
			// printf("(%i, %i, %i, %X), ", fdf->input_map[i][j].pos.x, fdf->input_map[i][j].pos.y, fdf->input_map[i][j].pos.z, fdf->input_map[i][j].color);
			printf("(%f, %f, %f, %X), ", fdf->input_map[i][j].pos.x, fdf->input_map[i][j].pos.y, fdf->input_map[i][j].pos.z, fdf->input_map[i][j].color);
			j++;
		}
		printf("\n");
		i++;
		j = 0;
	}
}

int	party(t_fdf *fdf)
{
	// usleep(100000);
	fdf->angle.z = deg_to_rad(5);
	// rotate(fdf);
	// project_iso(fdf);
	// transform(fdf, fdf->offset);
	// draw_background(fdf->img, fdf->win_size, fdf->bg_color);
	update_canvas(fdf);
	// draw_mesh(fdf);
	// mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_fdf	fdf;

	if (argc != 2)
	{
		ft_printf("Wrong number of arguments.\n");
		ft_printf("Use: ./fdf <mapfile>\n");
		exit(1);
	}
	init_fdf(&fdf);
	check_map_format(&fdf, argv[1]);
	init_maps(&fdf);
	read_map(&fdf, argv[1]);
	init_mlx(&fdf);
	update_canvas(&fdf);
	fdf.zoom = fit_zoom_to_windowsize(&fdf);
	fdf.angle.z = deg_to_rad(-90);
	update_canvas(&fdf);
	mlx_key_hook(fdf.win, &key_hook, &fdf);
	mlx_mouse_hook(fdf.win, &mouse_hook, &fdf);
	// mlx_loop_hook(fdf.mlx, &party, &fdf);
	mlx_loop(fdf.mlx);

	return (0);
}
