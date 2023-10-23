/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:36:07 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/23 17:19:19 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static t_vec2	isometric_projection(t_fdf *fdf, int x, int y, int z)
// {
// 	t_vec2	rtn;
// 	int		angle;
// 	double	zoom;

// 	angle = 45;
// 	zoom = 20;
// 	x -= 2 / 2;
// 	y -= 2 / 2;
// 	x *= zoom;
// 	y *= zoom;
// 	z *= zoom * 4 / 10;
// 	rtn.x = cos(deg_to_rad(angle)) * (y - 2 / 2)
// 		- cos(deg_to_rad(angle)) * (x - 2 / 2);
// 	rtn.y = -z * cos(deg_to_rad(angle * 2))
// 		+ sin(deg_to_rad(angle)) * (x - 2 / 2)
// 		+ sin(deg_to_rad(angle)) * (y - 2 / 2);
// 	rtn.x += fdf->win_size.x / 2;
// 	rtn.y += fdf->win_size.y / 2;
// 	return (rtn);
// }

void projectToIsometric(t_fdf *fdf, t_vec3 input, t_vec2 *output) {
    // Define the isometric transformation matrix
    double transformationMatrix[3][3] = {
        {sqrt(3) / 2, -1.0 / 2, 0},
        {0, 1.0, 0},
        {1.0 / sqrt(2), 1.0 / sqrt(2), 1.0}
    };

    // Apply the transformation matrix to the input point
    output->x = (transformationMatrix[0][0] * input.x + transformationMatrix[0][1] * input.y + transformationMatrix[0][2] * input.z) + fdf->win_size.x / 2;
    output->y = (transformationMatrix[1][0] * input.x + transformationMatrix[1][1] * input.y + transformationMatrix[1][2] * input.z) + fdf->win_size.y / 2;
}

// t_vec2 *set_2d_points(t_fdf *fdf, t_vec3 points[], int size)
// {
// 	int		i;
// 	t_vec2	*ret;
// 	t_vec3	point;

// 	i = 0;
// 	ret = malloc(size * sizeof(t_vec2));
// 	if (ret == NULL)
// 		return (NULL);
// 	while (i < size)
// 	{
// 		point = points[i];
// 		// ret[i] = isometric_projection(fdf, point.x, point.y, point.z);
// 		// projectToIsometric(fdf, point, &ret[i]);
// 		ret[i].x = (point.x - point.y) * cos(45.0) + (fdf->win_size.x / 2);
// 		ret[i].y = (point.x + point.y) * sin(45.0) - (point.z * 1) + (fdf->win_size.y / 2);
// 		i++;
// 	}
// 	return (ret);
// }

// t_vec2 **set_2d_points_grid(t_fdf *fdf, t_vec3 grid[10][10], int width, int height)
// {
// 	int		i;
// 	int		j;
// 	t_vec2	**ret;
// 	t_vec3	point;
// 	i = 0;
// 	ret = malloc(height * sizeof(t_vec2 *));
// 	if (ret == NULL)
// 		return (NULL);
// 	while (i < height)
// 	{
// 		j = 0;
// 		ret[i] = malloc(width * sizeof(t_vec2));
// 		while (j < width)
// 		{
// 			point = grid[i][j];
// 			ret[i][j].x = ft_round(fdf->zoom * (point.x - point.y)) * 0.841 + (fdf->win_size.x / 2);
// 			ret[i][j].y = ft_round(fdf->zoom * (point.x + point.y)) * 0.5 - (point.z * fdf->zoom) + (fdf->win_size.y / 2);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (ret);
// }

void	set_2d_points_grid(t_fdf *fdf)
{
	int		i;
	int		j;
	t_vec3	point;

	i = 0;
	while (i < fdf->map_size.y)
	{
		j = 0;
		while (j < fdf->map_size.x)
		{
			point = fdf->input_map[i][j].pos;
			fdf->map[i][j].pos.x = ft_round(fdf->zoom * (point.x - point.y)) * 0.841 + (fdf->win_size.x / 2);
			fdf->map[i][j].pos.y = ft_round(fdf->zoom * (point.x + point.y)) * 0.5 - (point.z * fdf->zoom) + (fdf->win_size.y / 2);
			j++;
		}
		i++;
	}
}
