/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:46:27 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 13:11:50 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_everything(t_fdf *fdf)
{
	if (fdf->mlx && fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->img && fdf->img->img)
	{
		mlx_destroy_image(fdf->mlx, fdf->img->img);
		free(fdf->img);
	}
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	ft_free_array((void **) fdf->input_map);
	ft_free_array((void **) fdf->map);
}

int	close_window(t_fdf *fdf)
{
	free_everything(fdf);
	exit(0);
}
