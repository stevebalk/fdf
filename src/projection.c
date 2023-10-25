/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:36:07 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/25 16:47:19 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project_iso(t_fdf *fdf)
{
	int		i;
	int		j;
	t_vec3i	point;

	i = 0;
	while (i < fdf->map_size.y)
	{
		j = 0;
		while (j < fdf->map_size.x)
		{
			point = fdf->input_map[i][j].pos;
			fdf->map[i][j].pos.x = ft_round(fdf->zoom * (point.x - point.y) * 0.841);
			fdf->map[i][j].pos.y = ft_round(fdf->zoom * (point.x + point.y) * 0.5 - (point.z * fdf->zoom));
			j++;
		}
		i++;
	}
}

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

void	transform(t_fdf *fdf, t_vec2i direction)
{
	int	i;
	int	j;

	if (!(direction.x == 0 && direction.y == 0))
	{
		i = 0;
		while (i < fdf->map_size.x)
		{
			j = 0;
			while (j < fdf->map_size.y)
			{
				fdf->map[j][i].pos.x += direction.x;
				fdf->map[j][i].pos.y += direction.y;
				j++;
			}
			i++;
		}
	}
}

// void	update_projection(t_fdf *fdf)
// {
	
// }

// void	rotate_x(t_fdf *fdf, float rad)
// {
// 	float	
// }