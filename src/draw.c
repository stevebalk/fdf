/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:28:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/25 12:48:22 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, t_vec2i pos, int color)
{
	char	*dst;

	if (pos.x < 0 || pos.y < 0 || pos.x > data->win_size.x
		|| pos.y > data->win_size.y)
		return ;
	dst = data->addr + (pos.y * data->line_length + pos.x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_data *data, t_vec2i start, t_vec2i end, int color)
{
	int	y_start;

	y_start = start.y;
	while (start.x < end.x)
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

void	draw_background(t_data *data, t_vec2i size, int color)
{
	t_vec2i	start;

	start.x = 0;
	start.y = 0;
	draw_rect(data, start, size, color);
}

/* Bresenham's algorithm */
void	draw_line(t_data *data, t_vec2i start, t_vec2i end, int color)
{
	t_line	line;
	int		e2;

	line.dx = ft_abs(end.x - start.x);
	line.sx = ft_sign(start.x - end.x) * -1;
	line.dy = -abs(end.y - start.y);
	line.sy = ft_sign(start.y - end.y) * -1;
	line.err = line.dx + line.dy;
	while (1)
	{
		my_mlx_pixel_put(data, start, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * line.err;
		if (e2 >= line.dy)
		{
			line.err += line.dy;
			start.x += line.sx;
		}
		if (e2 <= line.dx)
		{
			line.err += line.dx;
			start.y += line.sy;
		}
	}
}

// void	draw_point(t_data *data, t_vec2 pos, int size, int color)
// {
// 	draw_rect(data, (t_vec2){pos.x - size / 2, pos.y - size / 2}, (t_vec2){pos.x + size / 2, pos.y + size / 2}, color);
// }

// void	draw_cube(t_data *data, int size)
// {
// 	t_vec2	**cube;
// 	t_vec2	point;

// 	cube = malloc(sizeof(t_vec2 *) * 2);
// 	cube[0] = malloc(sizeof(t_vec2) * 4);
// 	cube[1] = malloc(sizeof(t_vec2) * 4);

// 	cube[0][0].x = 0;
// 	cube[0][0].y = 0;
// 	cube[0][1].x = size;
// 	cube[0][1].y = 0;
// 	cube[0][2].x = size;
// 	cube[0][2].y = size;
// 	cube[0][3].x = 0;
// 	cube[0][3].y = size;

// 	cube[1][0].x = 0;
// 	cube[1][0].y = 0;
// 	cube[1][1].x = size;
// 	cube[1][1].y = 0;
// 	cube[1][2].x = size;
// 	cube[1][2].y = size;
// 	cube[1][3].x = 0;
// 	cube[1][3].y = size;

// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (i < 2)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			point = cube[i][j];
// 			cube[i][j].x = ft_round((point.x - point.y) * 0.841 + (1920 / 2));
// 			cube[i][j].y = ft_round((i * size) - ((point.x + point.y) * 0.5) + (1080 / 2));
// 			j++;
// 		}
// 		i++;
// 	}
// 	printf("Cube:\n");
// 	for (int i=0; i<2; i++)
// 	{
// 		for (int j=0; j<4; j++)
// 		{
// 			printf("x: %d y: %d", cube[i][j].x, cube[i][j].y);
// 			printf("\n");
// 		}
// 		printf("\n");
// 	}
// 	i = 0;
// 	while (i < 2)
// 	{
// 		j = 0;
// 		while (j < 3)
// 		{
// 			draw_line(data, cube[i][j], cube[i][j + 1], WHITE);
// 			j++;
// 		}
// 		draw_line(data, cube[i][0], cube[i][3], WHITE);
// 		i++;
// 	}
// 	i = -1;
// 	while (i++ < 4)
// 		draw_line(data, cube[0][i], cube[1][i], YELLOW);
// 	// draw_line(data, (t_vec2){0,0}, (t_vec2){1920, 1080}, WHITE);
// }

void	draw_mesh(t_fdf *fdf)
{
	int	x;
	int	y;

	x = 0;
	while (x < fdf->map_size.y)
	{
		y = 0;
		while (y < fdf->map_size.x)
		{
			if (x != 0)
				draw_line(fdf->img, fdf->map[x][y].pos,
					fdf->map[x - 1][y].pos, fdf->input_map[x][y].color);
			if (y != 0)
				draw_line(fdf->img, fdf->map[x][y].pos,
					fdf->map[x][y - 1].pos, fdf->input_map[x][y].color);
			y++;
		}
		x++;
	}
}
