/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:28:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/01 15:45:19 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_data *data, t_vec2i pos, int color)
{
	char	*dst;

	if (pos.x < 0 || pos.y < 0 || pos.x >= data->win_size.x
		|| pos.y >= data->win_size.y)
		return ;
	dst = data->addr + (pos.y * data->line_length + pos.x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	is_line_visible(t_fdf *fdf, t_vec2i start, t_vec2i end)
{
	if ((start.x < 0 && end.x < 0)
		|| (start.x > fdf->win_size.x && end.x > fdf->win_size.x)
		|| (start.y < 0 && end.y < 0)
		|| (start.y > fdf->win_size.y && end.y > fdf->win_size.y))
		return (0);
	return (1);
}
