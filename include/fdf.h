/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:06:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/24 16:32:38 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "mlx_int.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <errno.h>

#ifndef FDF_H
# define FDF_H

/* Windowsize */
#define WIDTH	1920
#define HEIGHT	1080

typedef struct	s_line
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int err;
}				t_line;

typedef struct	s_vec2
{
	int	x;
	int	y;
}				t_vec2;

typedef struct	s_vec3
{
	int	x;
	int	y;
	int	z;
}				t_vec3;

typedef struct	s_vert3d
{
	t_vec3	pos;
	int		color;
}				t_vert3d;

typedef struct	s_vert2d
{
	t_vec2	pos;
	int		color;
}				t_vert2d;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	t_vec2	win_size;
	int		endian;
}				t_data;

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	t_vert2d	**map;
	t_vert3d	**input_map;
	t_vec2		win_size;
	t_vec2		map_size;
	t_vec2		pivot;
	int			cur_color;
	int			bg_color;
	int			default_color;
	int			zoom;
	t_data		*img;

}				t_fdf;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

/* KEYCODES */

#define ESC						65307
#define SPACE					32
#define ARROW_LEFT				65361
#define ARROW_DOWN				65364
#define ARROW_RIGHT				65363
#define ARROW_UP				65362

#define MOUSE_WHEEL_UP			4
#define MOUSE_WHEEL_DOWN		5
#define MOUSE_WHEEL_CLICK		2
#define MOUSE_CLICK_LEFT		1
#define MOUSE_CLICK_RIGHT		3
#define MOUSE_CLICK_FORWARD		9
#define MOUSE_CLICK_BACKWARD	8

/* COLORS */
#define WHITE	0x00FFFFFF
#define BLACK	0x00000000
#define RED		0x00FF0000
#define GREEN	0x0000FF00
#define BLUE	0x000000FF
#define YELLOW	0x00FFFF00
#define CYAN	0x0000FFFF
#define MAGENTA	0x00FF00FF

/* INIT */

void	init_fdf(t_fdf *fdf);
void	init_maps(t_fdf *fdf);

/* Map parsing */

void	check_map_format(t_fdf *fdf, char *filename);
void	read_map(t_fdf *fdf, char *filename);

/* ERROR */

void	error_msg(t_fdf *fdf, char *msg, int use_errno, int shall_exit);

/* DRAW */

void	my_mlx_pixel_put(t_data *data, t_vec2 vec2, int color);
void	draw_rect(t_data *data, t_vec2 start, t_vec2 end, int color);
void	draw_background(t_data *data, t_vec2 size, int color);
void	draw_line(t_data *data, t_vec2 start, t_vec2 end, int color);
void	draw_point(t_data *data, t_vec2 pos, int size, int color);
void	draw_cube(t_data *data, int size);
// void	redraw(t_fdf *fdf);
void	draw_mesh(t_fdf *fdf);

/* KEY HANDLING */

int		key_hook(int keycode, t_vars *vars);
int		mouse_hook(int keycode, void *param);
void	setup_controls(t_fdf *fdf);
void	mouse_click(int key, void *param);

/* MATH */

double	deg_to_rad(int deg);

/* PROJECTION */

int	fit_zoom_to_windowsize(t_fdf *fdf);
// void	set_2d_points_grid(t_fdf *fdf);
void	project_iso(t_fdf *fdf);
void	transform(t_fdf *fdf, t_vec2 direction);
void	zoom(t_fdf *fdf, int zoom);

/* MEMORY */

void	free_fdf(t_fdf *fdf);

#endif
