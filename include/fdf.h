/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:06:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/29 12:50:50 by sbalk            ###   ########.fr       */
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
#define WIDTH			1024
#define HEIGHT			768

#define ROTATION_ANGLE	5
#define ZOOM_MOD		1.5

/* For line calculation */
typedef struct	s_line
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int err;
	int err2;
}				t_line;

/* Vector 2 only integers */
typedef struct	s_vec2i
{
	int	x;
	int	y;
}				t_vec2i;

/* Vector 2 floating point */
typedef struct	s_vec2
{
	float	x;
	float	y;
}				t_vec2;

/* Vector 3 only integers */
typedef struct	s_vec3i
{
	int	x;
	int	y;
	int	z;
}				t_vec3i;

/* Vector 3 floating point */
typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

/* Vector 3 floating point vertice, saving position
color and if height is changeable */
typedef struct	s_vert3d
{
	t_vec3	pos;
	int		color;
	char	changeable;
}				t_vert3d;

/* Vector 2 integer vertice, saving position
and color */
typedef struct	s_vert2d
{
	t_vec2i	pos;
	int		color;
}				t_vert2d;

/* Saving data for mlx */
typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	t_vec2i	win_size;
	int		endian;
}				t_data;

/* Save rgb values in different variables */
typedef struct	s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

/* FdF main struct, saving all data that 
is needed everywhere in the program */
typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	t_vert2d	**map;
	t_vert3d	**input_map;
	t_vec2i		win_size;
	t_vec2i		map_size;
	t_vec2		pivot;
	int			cur_color;
	int			bg_color;
	int			default_color;
	float		zoom;
	float		zoom_mod;
	float		min_zoom;
	float		max_zoom;
	t_data		*img;
	t_vec3		angle;
	float		rotation_angle;
	t_vec2i		win_center;
	t_vec2i		offset;
	float			party;
}				t_fdf;

/*Struct for keyhook */
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
void	init_mlx(t_fdf *fdf);
void	init_maps(t_fdf *fdf);

/* Map parsing */

void	check_map_format(t_fdf *fdf, char *filename);
void	read_map(t_fdf *fdf, char *filename);

/* ERROR */

void	error_msg(t_fdf *fdf, char *msg, int use_errno, int shall_exit);

/* DRAW */

void	my_mlx_pixel_put(t_data *data, t_vec2i vec2, int color);
int		get_next_point(t_line *line, t_vec2i *start, t_vec2i end);
void	draw_rect(t_data *data, t_vec2i start, t_vec2i end, int color);
void	draw_background(t_data *data, t_vec2i size, int color);
void	draw_line(t_fdf *fdf, t_vec2i start, t_vec2i end, int color);
void	draw_point(t_data *data, t_vec2i pos, int size, int color);
void	draw_cube(t_data *data, int size);
void	draw_mesh(t_fdf *fdf);

void	draw_line_gradient(t_fdf *fdf, t_vert2d start, t_vert2d end);
void draw_gradient(t_fdf *fdf, t_vert3d start, t_vert3d end, int colorStart, int colorEnd);
// void	draw_gradient(t_fdf *fdf, t_vec2i start, t_vec2i end, int colorStart, int colorEnd);

/* KEY HANDLING */

// int		key_hook(int keycode, t_vars *vars);
int		key_hook(int keycode, t_fdf *fdf);
int	mouse_hook(int keycode, int x, int y, t_fdf *fdf);
// int		mouse_hook(int keycode, void *param);
void	setup_controls(t_fdf *fdf);
void	mouse_click(int key, void *param);

/* MATH */

double	deg_to_rad(int deg);

/* Manipulation */

void	change_height(t_fdf *fdf, float value);

/* PROJECTION */

float	fit_zoom_to_windowsize(t_fdf *fdf);
// void	set_2d_points_grid(t_fdf *fdf);
void	project_iso(t_fdf *fdf);
void	project_flat(t_fdf *fdf);
void	transform(t_fdf *fdf, t_vec2i direction);
void	zoom(t_fdf *fdf, int keycode);
void	apply_zoom(t_fdf *fdf, float zoom_mod);
void	rotate_x(t_vec3 *vec, float rad);
void	rotate_y(t_vec3 *vec, float rad);
void	rotate_z(t_vec3 *vec, float rad);
void	rotate(t_fdf *fdf);

/* MEMORY */

void	free_everything(t_fdf *fdf);

#endif
