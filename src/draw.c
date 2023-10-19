/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:28:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/02 16:59:48 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, t_vec2 pos, int color)
{
	char	*dst;

	if (pos.x < 0 || pos.y < 0 || pos.x > data->win_size.x || pos.y > data->win_size.y)
		return;
	dst = data->addr + (pos.y * data->line_length + pos.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_rect(t_data *data, t_vec2 start, t_vec2 end, int color)
{
	int	y_start;

	y_start = start.y;
	while(start.x < end.x)
	{
		start.y = y_start;
		while (start.y < end.y)
		{
			my_mlx_pixel_put(data, start, color);
			start.y++;
		}
		start.x++;
	}
}

void	draw_background(t_data *data, t_vec2 size, int color)
{
	t_vec2	start;

	start.x = 0;
	start.y = 0;

	draw_rect(data, start, size, color);
}

/* Bresenham's algorithm */
void	draw_line(t_data *data, t_vec2 start, t_vec2 end, int color)
{
	int	dx =  abs(end.x - start.x);
	int	sx = start.x < end.x ? 1 : -1;
	int	dy = -abs(end.y - start.y);
	int	sy = start.y < end.y ? 1 : -1; 
	int err = dx+dy, e2; /* error value e_xy */

	for(;;){  /* loop */
		my_mlx_pixel_put(data, start, color);
		if (start.x==end.x && start.y==end.y) break;
		e2 = 2*err;
		if (e2 >= dy) { err += dy; start.x += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; start.y += sy; } /* e_xy+e_y < 0 */
	}
}

void	draw_point(t_data *data, t_vec2 pos, int size, int color)
{
	draw_rect(data, (t_vec2){pos.x - size / 2, pos.y - size / 2}, (t_vec2){pos.x + size / 2, pos.y + size / 2}, color);
}

void	draw_cube(t_data *data, int size)
{
	t_vec2	**cube;
	t_vec2	point;

	cube = malloc(sizeof(t_vec2 *) * 2);
	cube[0] = malloc(sizeof(t_vec2) * 4);
	cube[1] = malloc(sizeof(t_vec2) * 4);

	cube[0][0].x = 0;
	cube[0][0].y = 0;
	cube[0][1].x = size;
	cube[0][1].y = 0;
	cube[0][2].x = size;
	cube[0][2].y = size;
	cube[0][3].x = 0;
	cube[0][3].y = size;

	cube[1][0].x = 0;
	cube[1][0].y = 0;
	cube[1][1].x = size;
	cube[1][1].y = 0;
	cube[1][2].x = size;
	cube[1][2].y = size;
	cube[1][3].x = 0;
	cube[1][3].y = size;


	int		i;
	int		j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 4)
		{
			point = cube[i][j];
			cube[i][j].x = ft_round((point.x - point.y) * 0.841 + (1920 / 2));
			cube[i][j].y = ft_round((i * size) - ((point.x + point.y) * 0.5) + (1080 / 2));
			j++;
		}
		i++;
	}
	printf("Cube:\n");
	for (int i=0; i<2; i++)
	{
		for (int j=0; j<4; j++)
		{
			printf("x: %d y: %d", cube[i][j].x, cube[i][j].y);
			printf("\n");
		}
		printf("\n");
	}
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 3)
		{
			draw_line(data, cube[i][j], cube[i][j + 1], WHITE);
			j++;
		}
		draw_line(data, cube[i][0], cube[i][3], WHITE);
		i++;
	}
	i = -1;
	while (i++ < 4)
		draw_line(data, cube[0][i], cube[1][i], YELLOW);
	// draw_line(data, (t_vec2){0,0}, (t_vec2){1920, 1080}, WHITE);
}

void	redraw(t_fdf *fdf)
{
	// free(fdf->test_final_points);
	// fdf->test_final_points = set_2d_points_grid(fdf, fdf->grid, 10, 10);
	// mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
}