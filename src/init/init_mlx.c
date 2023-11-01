/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:01:25 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/01 16:28:58 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_mlx_window(t_fdf *fdf)
{
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF");
	if (fdf->win == NULL)
		error_msg(fdf, "Error: mlx_new_window failed", 1, 1);
}

void	init_mlx_image(t_fdf *fdf, t_data **data, t_vec2i size)
{
	*data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		error_msg(fdf, "Error: init_mlx ft_calloc failed", 1, 1);
	(*data)->img = mlx_new_image(fdf->mlx, size.x, size.y);
	if ((*data)->img == NULL)
		error_msg(fdf, "Error: mlx_new_image failed", 0, 1);
	(*data)->addr = mlx_get_data_addr((*data)->img,
			&((*data)->bits_per_pixel),
			&((*data)->line_length), &((*data)->endian));
	if ((*data)->addr == NULL)
		error_msg(fdf, "Error: mlx_get_data_addr failed", 0, 1);
	(*data)->win_size = fdf->win_size;
}

void	init_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		error_msg(fdf, "Error: mlx_init failed", 1, 1);
	init_mlx_window(fdf);
	init_mlx_image(fdf, &fdf->img, fdf->win_size);
}
