/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:17:22 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 15:58:03 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Rotate vector3 around x axis */
void	rotate_x(t_vec3 *vec, float rad)
{
	float	old_y;

	old_y = vec->y;
	vec->y = old_y * cos(rad) + vec->z * sin(rad);
	vec->z = -old_y * sin(rad) + vec->z * cos(rad);
}

/* Rotate vector3 around y axis */
void	rotate_y(t_vec3 *vec, float rad)
{
	float	old_x;

	old_x = vec->x;
	vec->x = old_x * cos(rad) + vec->z * sin(rad);
	vec->z = -old_x * sin(rad) + vec->z * cos(rad);
}

/* Rotate vector3 around z axis */
void	rotate_z(t_vec3 *vec, float rad)
{
	float	old_x;
	float	old_y;

	old_x = vec->x;
	old_y = vec->y;
	vec->x = old_x * cos(rad) - old_y * sin(rad);
	vec->y = old_x * sin(rad) + old_y * cos(rad);
}

/* Set axis rotation */
int	change_rotation(float *axis, float degree)
{
	if (degree != 0.0)
	{
		*axis += deg_to_rad(degree);
		return (1);
	}
	return (0);
}
