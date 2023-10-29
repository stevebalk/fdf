/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:22:11 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/29 16:54:57 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Move the mesh in the given direction */
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
