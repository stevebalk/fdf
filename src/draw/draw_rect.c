/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:05:42 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/01 13:24:44 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_rect(t_data *data, t_vec2i start, t_vec2i end, int color)
{
	int	y_start;

	y_start = start.y;
	while (start.x < end.x)
	{
		start.y = y_start;
		while (start.y < end.y)
		{
			pixel_put(data, start, color);
			start.y++;
		}
		start.x++;
	}
}

void	draw_background(t_data *data, t_vec2i size, int color)
{
	t_vec2i	start;

	start.x = 0;
	start.y = 0;
	draw_rect(data, start, size, color);
}
