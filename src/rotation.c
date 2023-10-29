/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:17:22 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/29 16:21:42 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Rotate vector3 around x axis */
static void	rotate_x(t_vec3 *vec, float rad)
{
	float	old_y;

	old_y = vec->y;
	vec->y = old_y * cos(rad) + vec->z * sin(rad);
	vec->z = -old_y * sin(rad) + vec->z * cos(rad);
}

/* Rotate vector3 around y axis */
static void	rotate_y(t_vec3 *vec, float rad)
{
	float	old_x;

	old_x = vec->x;
	vec->x = old_x * cos(rad) + vec->z * sin(rad);
	vec->z = -old_x * sin(rad) + vec->z * cos(rad);
}

/* Rotate vector3 around z axis */
static void	rotate_z(t_vec3 *vec, float rad)
{
	float	old_x;
	float	old_y;

	old_x = vec->x;
	old_y = vec->y;
	vec->x = old_x * cos(rad) - old_y * sin(rad);
	vec->y = old_x * sin(rad) + old_y * cos(rad);
}

/* Apply all rotations for this drawcall */
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
