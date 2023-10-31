/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:36:07 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 21:23:07 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Projects to iso perspective */
void	project_iso(t_fdf *fdf, t_vec3 *src, t_vec2i *dst)
{
	rotate_z(src, fdf->angle.z);
	rotate_x(src, fdf->angle.x);
	rotate_y(src, fdf->angle.y);
	dst->x = ft_round(((src->x - src->y) * ISO_COS_VALUE) * fdf->zoom);
	dst->y = ft_round((-src->z + (src->x + src->y)
				* ISO_SIN_VALUE) * fdf->zoom);
}

/* Projects a top down view */
void	project_flat(t_fdf *fdf, t_vec3 *src, t_vec2i *dst)
{
	rotate_z(src, fdf->angle.z);
	dst->x = ft_round(src->x * fdf->zoom);
	dst->y = ft_round(src->y * fdf->zoom);
}
