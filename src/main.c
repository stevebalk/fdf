/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:41:41 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/02 18:39:33 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "fdf.h"

// mlx_new_image maybe buffer possible? overlay?

int	main(void)
{
	t_data	img;	// Image data, necessary for mlx
	t_fdf	fdf;

	init_fdf(&fdf);
	img.img = mlx_new_image(fdf.mlx, fdf.win_size.x, fdf.win_size.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.win_size = fdf.win_size;
	draw_background(&img, fdf.win_size, fdf.bg_color);

	/* Draw string on the canvas */

	/* Print screen size*/
	// mlx_get_screen_size(mlx, &sizex, &sizey);
	// printf("Screen x: %d, y: %d\n", sizex, sizey);


	// end_points = set_2d_points(&fdf, points, 4);

	int rows = 10; // Number of rows
    int cols = 10; // Number of columns

    t_vec3 grid[rows][cols];

    // Fill the grid with t_vec3 structures
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            grid[x][y].x = x;
            grid[x][y].y = y;
            grid[x][y].z = 0;
        }
    }
	grid[0][0].z = -1;
	grid[1][1].z = 1;
	grid[4][4].z = 1;
	grid[4][5].z = 1;
	grid[5][4].z = 1;
	grid[5][5].z = 1;
	grid[9][9].z = 1;
	// fdf.grid = &grid;
	fdf.img	 = &img;
	fdf.test_final_points = set_2d_points_grid(&fdf, grid, rows, cols);

	printf("Starting vectors:\n");
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			printf("(%d, %d, %d) ", grid[x][y].x, grid[x][y].y, grid[x][y].z);
		}
		printf("\n");
	}
	printf("End vectors:\n");
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			printf("(%d, %d) ", fdf.test_final_points[x][y].x, fdf.test_final_points[x][y].y);
		}
		printf("\n");
	}


	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			if (x != 0)
				draw_line(&img, fdf.test_final_points[x][y], fdf.test_final_points[x - 1][y], fdf.cur_color);
			if (y != 0)
				draw_line(&img, fdf.test_final_points[x][y], fdf.test_final_points[x][y - 1], fdf.cur_color);
		}
	}
	printf("ZOOM: %d\n", fdf.zoom);

	// draw_cube(&img, fdf.win_size.y / 2);
	
	/* Keyhook */
	mlx_key_hook(fdf.win, key_hook, &fdf);
	// mlx_mouse_hook(fdf.win, mouse_hook, &fdf);
	setup_controls(&fdf);

	mlx_put_image_to_window(fdf.mlx, fdf.win, img.img, 0, 0);
	mlx_loop(fdf.mlx);
	return (0);
}
