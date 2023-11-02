/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:06:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/02 14:05:43 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx_int.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <errno.h>

/* Windowsize */

// #define WIDTH			640
// #define HEIGHT			480
// #define WIDTH			1024
// #define HEIGHT			768
# define WIDTH			1920
# define HEIGHT			1080

/* Settings */
# define ROTATION_STEP		5
# define ZOOM_MOD			1.5
# define ZOOM_MIN			1
# define ZOOM_MAX			250
# define OFFSET_STEP			50
# define HEIGHT_STEP			1.0
# define DEFAULT_COLOR		0x00FFFFFF
# define BACKGROUND_COLOR	0x00000019

/* Projection value */
# define ISO_PROJECTION	1
# define TOP_VIEW		2

/* Cos(0.523599) and Sin(0.523599) isometric constant values */

# define ISO_COS_VALUE 0.86602540378
# define ISO_SIN_VALUE 0.49999999999

/* For line calculation */
typedef struct s_line
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	err2;
}				t_line;

/* Vector 2 only integers */
typedef struct s_vec2i
{
	int	x;
	int	y;
}				t_vec2i;

/* Vector 2 floating point */
typedef struct s_vec2
{
	float	x;
	float	y;
}				t_vec2;

/* Vector 3 only integers */
typedef struct s_vec3i
{
	int	x;
	int	y;
	int	z;
}				t_vec3i;

/* Vector 3 floating point */
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

/* Vector 3 floating point vertice, position
color, altitude color and if height is modifiable */
typedef struct s_vert3d
{
	t_vec3	pos;
	int		color;
	int		alt_color;
	char	changeable;
}				t_vert3d;

/* Vector 2 integer vertice, saving position
and color */
typedef struct s_vert2d
{
	t_vec2i	pos;
	int		color;
}				t_vert2d;

/* Data for mlx */
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	t_vec2i	win_size;
	int		endian;
}				t_data;

/* Save rgb values in different variables */
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

/* FdF main struct, data that 
is used everywhere */
typedef struct s_fdf
{
	void			*mlx;
	void			*win;
	t_data			*img;
	t_vert2d		**map;
	t_vert3d		**input_map;
	t_vec2i			win_size;
	t_vec2i			map_size;
	t_vec2i			win_center;
	t_vec2			pivot;
	t_vec2i			offset;
	int				use_alti_colors;
	int				bg_color;
	int				default_color;
	float			zoom;
	t_vec3			angle;
	unsigned int	projection;
	t_vec3i			autorotate;
}					t_fdf;

/* KEYCODES */

# define MOUSE_WHEEL_UP			4
# define MOUSE_WHEEL_DOWN		5
# define MOUSE_WHEEL_CLICK		2
# define MOUSE_CLICK_LEFT		1
# define MOUSE_CLICK_RIGHT		3
# define MOUSE_CLICK_FORWARD		9
# define MOUSE_CLICK_BACKWARD	8

/* COLORS */
# define WHITE		0x00FFFFFF
# define LIGHT_GREY	0x00BBBBBB
# define BLACK		0x00000000
# define RED		0x00FF0000
# define DARK_RED	0x00880000
# define GREEN		0x0000FF00
# define DARK_GREEN	0x00008800
# define BLUE		0x000000FF
# define DARK_BLUE	0x00000088
# define YELLOW		0x00FFFF00
# define CYAN		0x0000FFFF
# define MAGENTA	0x00FF00FF

/* INIT */

void	init_fdf(t_fdf *fdf);
void	init_mlx(t_fdf *fdf);
void	init_maps(t_fdf *fdf);
int		init_iso_projection(t_fdf *fdf);
int		init_flat_projection(t_fdf *fdf);

/* Map parsing */

void	check_map_format(t_fdf *fdf, char *filename);
void	read_map(t_fdf *fdf, char *filename);
void	set_altitude_color(t_fdf *fdf);

/* DRAW */

void	pixel_put(t_data *data, t_vec2i vec2, int color);
void	draw_background(t_data *data, t_vec2i size, int color);
void	draw_hud(t_fdf *fdf, int x, int y, int col);
void	draw_rect(t_data *data, t_vec2i start, t_vec2i end, int color);
int		is_line_visible(t_fdf *fdf, t_vec2i start, t_vec2i end);
int		get_next_point(t_line *line, t_vec2i *start, t_vec2i end);
void	draw_line(t_fdf *fdf, t_vec2i start, t_vec2i end, int color);
void	draw_line_gradient(t_fdf *fdf, t_vert2d start, t_vert2d end);
void	draw_mesh(t_fdf *fdf);
void	update_canvas(t_fdf *fdf);

/* KEY HANDLING */

void	init_keyhooks(t_fdf *fdf);
int		key_hook(int keycode, t_fdf *fdf);
int		mouse_hook(int keycode, int x, int y, t_fdf *fdf);
int		projection_keys_pressed(int keycode, t_fdf *fdf);
int		zoom_keys_pressed(int keycode, t_fdf *fdf);
int		height_keys_pressed(int keycode, t_fdf *fdf);
int		rotation_keys_pressed(int keycode, t_fdf *fdf);
int		movement_keys_pressed(int keycode, t_fdf *fdf);

/* MATH */

double	deg_to_rad(double deg);
double	rad_to_degree(double rad);

/* Manipulation */

void	transform(t_fdf *fdf, t_vec2i direction);
void	rotate_x(t_vec3 *vec, float rad);
void	rotate_y(t_vec3 *vec, float rad);
void	rotate_z(t_vec3 *vec, float rad);
int		change_height(t_fdf *fdf, float value);
int		change_offset(int *axis, int value);
int		change_rotation(float *axis, float value);
int		zoom_in(t_fdf *fdf, float value);
int		zoom_out(t_fdf *fdf, float value);
float	fit_zoom_to_windowsize(t_fdf *fdf);
void	apply_transformations(t_fdf *fdf, t_vec3 *src, t_vec2i *dst);
int		autorotate(t_fdf *fdf);
void	toggle_altitude_color(t_fdf *fdf);

/* PROJECTION */

void	project_iso(t_fdf *fdf, t_vec3 *src, t_vec2i *dst);
void	project_flat(t_fdf *fdf, t_vec3 *src, t_vec2i *dst);

/* MEMORY */

void	free_everything(t_fdf *fdf);

/* ERROR */

void	error_msg(t_fdf *fdf, char *msg, int use_errno, int shall_exit);

/* Exit */

int		close_window(t_fdf *fdf, int error);

#endif
