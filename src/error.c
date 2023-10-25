/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:33:06 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/25 14:54:14 by sbalk            ###   ########.fr       */
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

void	error_msg(t_fdf *fdf, char *msg, int use_errno, int shall_exit)
{
	ft_putendl_fd(msg, 2);
	if (shall_exit)
	{
		free_everything(fdf);
		if (use_errno)
			exit(errno);
		exit(EXIT_FAILURE);
	}
}
