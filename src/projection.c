/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:36:07 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/26 15:55:26 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	project_iso(t_fdf *fdf)
// {
// 	int		i;
// 	int		j;
// 	t_vec3i	point;

// 	i = 0;
// 	while (i < fdf->map_size.y)
// 	{
// 		j = 0;
// 		while (j < fdf->map_size.x)
// 		{
// 			point = fdf->input_map[i][j].pos;
// 			fdf->map[i][j].pos.x = ft_round(fdf->zoom * (point.x - point.y) * 0.841);
// 			fdf->map[i][j].pos.y = ft_round(fdf->zoom * (point.x + point.y) * 0.5 - (point.z * fdf->zoom));
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	project_iso(t_fdf *fdf)
// {
// 	int		i;
// 	int		j;
// 	float	_cos = cos(deg_to_rad(-30));
// 	float	_sin = sin(deg_to_rad(-30));
// 	t_vec3i	point;

// 	i = 0;
// 	while (i < fdf->map_size.y)
// 	{
// 		j = 0;
// 		while (j < fdf->map_size.x)
// 		{
// 			point = fdf->input_map[i][j].pos;
// 			fdf->map[i][j].pos.x = ft_round((point.x * _cos - point.y * _sin) * fdf->zoom);
// 			fdf->map[i][j].pos.y = ft_round((fdf->zoom * (point.x * _sin + point.y * _cos) * deg_to_rad(30))  * fdf->zoom);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	project_iso(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map_size.x)
	{
		j = 0;
		while (j < fdf->map_size.y)
		{
			fdf->map[j][i].pos.x = ft_round(((fdf->input_map[j][i].pos.x - fdf->input_map[j][i].pos.y) * cos(0.523599)) * fdf->zoom);
			fdf->map[j][i].pos.y = ft_round((-fdf->input_map[j][i].pos.z + (fdf->input_map[j][i].pos.x + fdf->input_map[j][i].pos.y) * sin(0.523599)) * fdf->zoom);
			j++;
		}
		i++;
	}
}

void	transform(t_fdf *fdf, t_vec2i direction)
{
	int	i;
	int	j;


	i = 0;
	while (i < fdf->map_size.x)
	{
		j = 0;
		while (j < fdf->map_size.y)
		{
			fdf->map[j][i].pos.x += fdf->win_center.x + direction.x;
			fdf->map[j][i].pos.y += fdf->win_center.y + direction.y;
			j++;
		}
		i++;
	}
}

void	rotate_x(t_vec3 *vec, float rad)
{
	float	old_y;

	old_y = vec->y;
	vec->y = old_y * cos(rad) + vec->z * sin(rad);
	vec->z = -old_y * sin(rad) + vec->z * cos(rad);
}

void	rotate_y(t_vec3 *vec, float rad)
{
	float	old_x;

	old_x = vec->x;
	vec->x = old_x * cos(rad) + vec->z * sin(rad);
	vec->z = -old_x * sin(rad) + vec->z * cos(rad);
}

void	rotate_z(t_vec3 *vec, float rad)
{
	float	old_x;
	float	old_y;

	old_x = vec->x;
	old_y = vec->y;
	vec->x = old_x * cos(rad) - old_y * sin(rad);
	vec->y = old_x * sin(rad) + old_y * cos(rad);
}

void	rotate(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	if (fdf->angle.x != 0.0 || fdf->angle.y != 0.0 || fdf->angle.z != 0.0)
	{
		while (i < fdf->map_size.x)
		{
			j = 0;
			while (j < fdf->map_size.y)
			{
				if (fdf->angle.z != 0.0)
					rotate_z(&fdf->input_map[j][i].pos, fdf->angle.z);
				if (fdf->angle.x != 0.0)
					rotate_x(&fdf->input_map[j][i].pos, fdf->angle.x);
				if (fdf->angle.y != 0.0)
					rotate_y(&fdf->input_map[j][i].pos, fdf->angle.y);
				j++;
			}
			i++;
		}
		fdf->angle.x = 0.0;
		fdf->angle.y = 0.0;
		fdf->angle.z = 0.0;
	}
}

void	update_projection(t_fdf *fdf)
{
	// int	i;
	// int	j;

	// i = 0;
	// while (i < fdf->map_size.x)
	// {
	// 	j = 0;
	// 	while (j < fdf->map_size.y)
	// 	{
	// 		// fdf->map[j][i].pos.x += direction.x;
	// 		// fdf->map[j][i].pos.y += direction.y;
	// 		j++;
	// 	}
	// 	i++;
	// }
	project_iso(fdf);
}
