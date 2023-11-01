/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_projections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:41:49 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/01 13:15:31 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_iso_projection(t_fdf *fdf)
{
	fdf->angle.x = 0;
	fdf->angle.y = 0;
	fdf->zoom = 1;
	fdf->angle.z = deg_to_rad(-90);
	fdf->zoom = fit_zoom_to_windowsize(fdf);
	return (1);
}

int	init_flat_projection(t_fdf *fdf)
{
	fdf->angle.x = 0;
	fdf->angle.y = 0;
	fdf->angle.z = 0;
	fdf->zoom = 1;
	fdf->zoom = fit_zoom_to_windowsize(fdf);
	return (1);
}
