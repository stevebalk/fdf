/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:41:41 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/24 14:58:31 by sbalk            ###   ########.fr       */
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
			printf("(%i, %i, %i, %X), ", fdf->input_map[i][j].pos.x, fdf->input_map[i][j].pos.y, fdf->input_map[i][j].pos.z, fdf->input_map[i][j].color);
			j++;
		}
		printf("\n");
		i++;
		j = 0;
	}
}

void	init_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->map = ft_calloc(fdf->map_size.y + 1, sizeof(t_vert2d *));
	if (fdf->map == NULL)
		error_msg(fdf, "Error: ft_calloc failed" , 1, 1);
	while (i < fdf->map_size.x)
	{
		fdf->map[i] = ft_calloc(fdf->map_size.x, sizeof(t_vert2d));
		if (fdf->map[i] == NULL)
			error_msg(fdf, "Error: ft_calloc failed" , 1, 1);
		i++;
	}
}

// mlx_new_image maybe buffer possible? overlay?

int	main(int argc, char *argv[])
{
	t_data	img;	// Image data, necessary for mlx
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
	img.img = mlx_new_image(fdf.mlx, fdf.win_size.x, fdf.win_size.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.win_size = fdf.win_size;
	fdf.img	 = &img;
	draw_background(&img, fdf.win_size, fdf.bg_color);
	// ft_printf("Height: %d\n", fdf.map_size.y);

	set_2d_points_grid(&fdf);
	draw_mesh(&fdf);
	// printf("End vectors:\n");
	// for (int x = 0; x < fdf.map_size.y; x++) {
	// 	for (int y = 0; y < fdf.map_size.x; y++) {
	// 		printf("(%d, %d) ", fdf.map[x][y].pos.x, fdf.map[x][y].pos.y);
	// 	}
	// 	printf("\n");
	// }

	/* Draw string on the canvas */

	/* Print screen size*/
	// mlx_get_screen_size(mlx, &sizex, &sizey);
	// printf("Screen x: %d, y: %d\n", sizex, sizey);


	// end_points = set_2d_points(&fdf, points, 4);

	// int rows = 10; // Number of rows
    // int cols = 10; // Number of columns

    // t_vec3 grid[rows][cols];

    // Fill the grid with t_vec3 structures
    // for (int x = 0; x < rows; x++) {
    //     for (int y = 0; y < cols; y++) {
    //         grid[x][y].x = x;
    //         grid[x][y].y = y;
    //         grid[x][y].z = 0;
    //     }
    // }
	// grid[0][0].z = -1;
	// grid[1][1].z = 1;
	// grid[4][4].z = 1;
	// grid[4][5].z = 1;
	// grid[5][4].z = 1;
	// grid[5][5].z = 1;
	// grid[9][9].z = 1;
	// fdf.grid = &grid;
	// fdf.test_final_points = set_2d_points_grid(&fdf, grid, rows, cols);

	// printf("Starting vectors:\n");
	// for (int x = 0; x < rows; x++) {
	// 	for (int y = 0; y < cols; y++) {
	// 		printf("(%d, %d, %d) ", grid[x][y].x, grid[x][y].y, grid[x][y].z);
	// 	}
	// 	printf("\n");
	// }


	// for (int x = 0; x < fdf.map_size.y; x++) {
	// 	for (int y = 0; y < fdf.map_size.x; y++) {
	// 		if (x != 0)
	// 			draw_line(&img, fdf.map[x][y].pos, fdf.map[x - 1][y].pos, fdf.input_map[x][y].color);
	// 		if (y != 0)
	// 			draw_line(&img, fdf.map[x][y].pos, fdf.map[x][y - 1].pos, fdf.input_map[x][y].color);
	// 	}
	// }
	// draw_line(&img, (t_vec2){0, 0}, (t_vec2){500, 500}, fdf.default_color);
	// printf("ZOOM: %d\n", fdf.zoom);

	// draw_cube(&img, fdf.win_size.y / 2);
	
	/* Keyhook */
	mlx_key_hook(fdf.win, key_hook, &fdf);
	// mlx_mouse_hook(fdf.win, mouse_hook, &fdf);
	// setup_controls(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, img.img, 0, 0);
	mlx_loop(fdf.mlx);
	free_fdf(&fdf);

	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	t_fdf fdf;

// 	init_fdf(&fdf);
// 	if (argc != 2)
// 	{
// 		ft_printf("Wrong number of arguments.\n");
// 		ft_printf("Use: ./fdf <mapfile>\n");
// 		exit(1);
// 	}
// 	read_map(&fdf, argv[1]);
// 	print_input_map(&fdf);
// }