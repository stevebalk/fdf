/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:36:07 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/29 16:29:52 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Projects to iso perspective */
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

/* Projects a top down view */
void	project_flat(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map_size.x)
	{
		j = 0;
		while (j < fdf->map_size.y)
		{
			fdf->map[j][i].pos.x = fdf->input_map[j][i].pos.x * fdf->zoom;
			fdf->map[j][i].pos.y = fdf->input_map[j][i].pos.y * fdf->zoom;
			j++;
		}
		i++;
	}
}
