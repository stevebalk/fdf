/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:41:41 by sbalk             #+#    #+#             */
/*   Updated: 2023/09/25 19:08:54 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "fdf.h"

typedef struct	s_vec2
{
	int	x;
	int	y;
}				t_vec2;

typedef struct	s_rect2
{
	t_vec2	pos;
	t_vec2	size;
}				t_rect2;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;


typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, t_vec2 vec2, int color)
{
	char	*dst;

	dst = data->addr + (vec2.y * data->line_length + vec2.x * (data->bits_per_pixel / 8));
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
/* DDS ALGO */
// void	draw_line(t_data *data, t_vec2 start, t_vec2 end, int color)
// {
// 	int		dx;
// 	int		dy;
// 	int		steps;
// 	float	x_increment;
// 	float	y_increment;

// 	dx = end.x - start.x;
// 	dy = end.y - start.y;

// 	if (ft_abs(dx) > ft_abs(dy))
// 		steps = ft_abs(dx);
// 	else
// 		steps = ft_abs(dy);
// 	x_increment = dx / (float) steps;
// 	y_increment = dy / (float) steps;

// 	for(int i=0; i < steps; i++)
// 	{
// 		start.x = ft_round(start.x + x_increment);
// 		start.y = ft_round(start.y + y_increment);
// 		my_mlx_pixel_put(data, start, color);
// 	}
// }

int	ft_sign(int num)
{
	if (num < 0)
		return (-1);
	else if (num > 0)
		return (1);
	else
		return (0);
}

/* Bresenham's algorithm */
void	draw_line(t_data *data, t_vec2 start, t_vec2 end, int color)
{
	// int		dx;
	// int		dy;
	// int		p;

	// dx = end.x - start.x;
	// dy = end.y - start.y;

	// p = 2*dy - dx;

	// while(start.x<end.x)
	// {
	// 	if(p >= 0)
	// 	{
	// 		my_mlx_pixel_put(data, start, color);
	// 		start.y++;
	// 		p += 2*dy - 2*dx;
	// 	}
	// 	else
	// 	{
	// 		my_mlx_pixel_put(data, start, color);
	// 		p += 2*dy;
	// 	}
	// 	start.x++;
	// }
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

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		exit(0);
	if (vars)
		printf("%d\n", keycode);
	return (0);
}

// t_vec2	get_circle_pos(t_vec2 start, int length, int steps)
// {
	
// }

// mlx_new_image maybe buffer possible? overlay?

int	main(void)
{
	void	*mlx;
	void	*mlx_window;
	t_data	img;	// Image data, necessary for mlx
	t_vec2	windowsize	= {1920, 1080};
	int	sizex = 0;
	int	sizey = 0;
	t_vec2	start		= {50, 50};	// Start position for stuff
	t_vec2	end			= {100, 150};	// End position for stuff
	int		bg_color		= WHITE;
	int		line_color		= BLUE;
	t_vars	vars;	// For keyhook

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, windowsize.x, windowsize.y, "WOW");
	img.img = mlx_new_image(mlx, windowsize.x, windowsize.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_background(&img, windowsize, bg_color);

	/* Draw string on the canvas */

	/* Print screen size*/
	mlx_get_screen_size(mlx, &sizex, &sizey);
	printf("Screen x: %d, y: %d\n", sizex, sizey);

	/* Keyhook */
	vars.mlx = mlx;
	vars.win = mlx_window;
	mlx_key_hook(vars.win, key_hook, &vars);
	// mlx_string_put(mlx, mlx_window, 100, 100, BLACK, "HELLO WORLDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);

	while (end.x < windowsize.x)`
	{
		draw_background(&img, windowsize, bg_color);
		draw_line(&img, start, end, BLUE);
		start.x++;
		end.x++;
		bg_color--;
		usleep(5000);
		mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	}
	draw_line(&img, start, end, line_color);
	mlx_loop(mlx);
	mlx_window = mlx_window;
}
