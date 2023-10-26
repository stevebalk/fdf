/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:41:41 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/26 15:47:32 by sbalk            ###   ########.fr       */
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

// void	init_map(t_fdf *fdf)
// {
// 	int	i;

// 	i = 0;
// 	fdf->map = ft_calloc(fdf->map_size.y + 1, sizeof(t_vert2d *));
// 	if (fdf->map == NULL)
// 		error_msg(fdf, "Error: ft_calloc failed" , 1, 1);
// 	while (i < fdf->map_size.x)
// 	{
// 		fdf->map[i] = ft_calloc(fdf->map_size.x, sizeof(t_vert2d));
// 		if (fdf->map[i] == NULL)
// 			error_msg(fdf, "Error: ft_calloc failed" , 1, 1);
// 		i++;
// 	}
// }

// mlx_new_image maybe buffer possible? overlay?

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
	// print_input_map(&fdf);
	init_mlx(&fdf);
	draw_background(fdf.img, fdf.win_size, fdf.bg_color);
	project_iso(&fdf);
	fdf.zoom = fit_zoom_to_windowsize(&fdf);
	// fdf.zoom = 5;
	rotate(&fdf);
	project_iso(&fdf);
	transform(&fdf, fdf.offset);

	draw_mesh(&fdf);
	/* Keyhook */
	mlx_key_hook(fdf.win, &key_hook, &fdf);
	mlx_mouse_hook(fdf.win, &mouse_hook, &fdf);
	// mlx_mouse_hook(fdf.win, mouse_hook, &fdf);
	// setup_controls(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img->img, 0, 0);
	mlx_loop(fdf.mlx);

	return (0);
}
