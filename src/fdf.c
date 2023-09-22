/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:41:41 by sbalk             #+#    #+#             */
/*   Updated: 2023/09/21 18:07:23 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "fdf.h"

typedef struct	s_vec2
{
	float	x;
	float	y;
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
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
			my_mlx_pixel_put(data, start.x, start.y, color);
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
void	draw_line(t_data *data, t_vec2 start, t_vec2 end, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	x_increment;
	float	y_increment;

	dx = end.x - start.x;
	dy = end.y - start.y;

	if (ft_abs(dx) > ft_abs(dy))
		steps = ft_abs(dx);
	else
		steps = ft_abs(dy);
	x_increment = dx / (float) steps;
	y_increment = dy / (float) steps;

	for(int i=0; i < steps; i++)
	{
		start.x = ft_round(start.x + x_increment);
		start.y = ft_round(start.y + y_increment);
		my_mlx_pixel_put(data, start.x, start.y, color);
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

// mlx_new_image maybe buffer possible? overlay?

int	main(void)
{
	void	*mlx;
	void	*mlx_window;
	t_data	img;	// Image data, necessary for mlx
	t_vec2	windowsize	= {1920, 1080};
	int	sizex = 0;
	int	sizey = 0;
	// t_vec2	start		= {300, 400};	// Start position for stuff
	// t_vec2	end			= {800, 900};	// End position for stuff
	int		color		= WHITE;
	t_vars	vars;	// For keyhook

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, windowsize.x, windowsize.y, "WOW");
	img.img = mlx_new_image(mlx, windowsize.x, windowsize.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_background(&img, windowsize, color);

	/* Draw string on the canvas */

	/* Print screen size*/
	mlx_get_screen_size(mlx, &sizex, &sizey);
	printf("Screen x: %d, y: %d\n", sizex, sizey);

	/* Keyhook */
	vars.mlx = mlx;
	vars.win = mlx_window;
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_string_put(mlx, mlx_window, 100, 100, BLACK, "HELLO WORLDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);

	// while (end.x < windowsize.x)
	// {
	// 	draw_background(&img, windowsize, color);
	// 	draw_line(&img, start, end, BLUE);
	// 	start.x++;
	// 	end.x++;
	// 	color--;
	// 	usleep(5000);
	// 	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	// }
	mlx_loop(mlx);
	mlx_window = mlx_window;
}
