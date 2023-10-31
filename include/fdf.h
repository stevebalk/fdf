/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:06:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 15:23:57 by sbalk            ###   ########.fr       */
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
// #define WIDTH			1024
// #define HEIGHT			768
#define WIDTH			1920
#define HEIGHT			1080

/* Settings */
#define ROTATION_STEP		5
#define ZOOM_MOD			1.5
#define ZOOM_MIN			1
#define ZOOM_MAX			30
#define OFFSET_STEP			50
#define HEIGHT_STEP			1.0
#define DEFAULT_COLOR		0x00FFFFFF
#define BACKGROUND_COLOR	0x00000019

/* cos(0.523599) and sin(0.523599) isometric constant values */

#define ISO_COS_VALUE 0.86602540378
#define ISO_SIN_VALUE 0.49999999999

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
	t_data		*img;
	t_vert2d	**map;
	t_vert3d	**input_map;
	t_vec2i		win_size;
	t_vec2i		map_size;
	t_vec2i		win_center;
	t_vec2		pivot;
	t_vec2i		offset;
	int			bg_color;
	int			default_color;
	float		zoom;
	t_vec3		angle;
}				t_fdf;

/*Struct for keyhook */
typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

/* KEYCODES */

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
void	update_canvas(t_fdf *fdf);

void	draw_line_gradient(t_fdf *fdf, t_vert2d start, t_vert2d end);

/* KEY HANDLING */

void	init_keyhooks(t_fdf *fdf);
int		key_hook(int keycode, t_fdf *fdf);
int		mouse_hook(int keycode, int x, int y, t_fdf *fdf);

/* MATH */

double	deg_to_rad(double deg);
double	rad_to_degree(double rad);

/* Manipulation */

void	transform(t_fdf *fdf, t_vec2i direction);
void	rotate(t_fdf *fdf);
void	rotate_x(t_vec3 *vec, float rad);
void	rotate_y(t_vec3 *vec, float rad);
void	rotate_z(t_vec3 *vec, float rad);
int		change_height(t_fdf *fdf, float value);
int		change_offset(int *axis, int value);
int		change_rotation(float *axis, float value);
int		zoom_in(t_fdf *fdf, float value);
int		zoom_out(t_fdf *fdf, float value);

/* PROJECTION */

float	fit_zoom_to_windowsize(t_fdf *fdf);
void	project_iso(t_fdf *fdf);
void	project_flat(t_fdf *fdf);

/* MEMORY */

void	free_everything(t_fdf *fdf);

/* Exit */

int	close_window(t_fdf *fdf);

#endif
