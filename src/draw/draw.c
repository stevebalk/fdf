/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:28:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 18:09:15 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, t_vec2i pos, int color)
{
	char	*dst;

	if (pos.x < 0 || pos.y < 0 || pos.x >= data->win_size.x
		|| pos.y >= data->win_size.y)
		return ;
	dst = data->addr + (pos.y * data->line_length + pos.x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
