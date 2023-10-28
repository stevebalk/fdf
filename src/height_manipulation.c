/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   height_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:48:28 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/27 17:09:41 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_height(t_fdf *fdf, float value)
{
	int			i;
	int			j;
	t_vert3d	*point;

	i = 0;
	while (i < fdf->map_size.x)
	{
		j = 0;
		while (j < fdf->map_size.y)
		{
			point = &fdf->input_map[j][i];
			if (point->changeable)
				point->pos.z += value;
			j++;
		}
		i++;
	}
}
