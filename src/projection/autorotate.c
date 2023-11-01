/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autorotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:25:53 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/01 15:41:53 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	autorotate(t_fdf *fdf)
{
	if (fdf->autorotate.x || fdf->autorotate.y || fdf->autorotate.z)
	{
		change_rotation(&fdf->angle.x, ROTATION_STEP * fdf->autorotate.x);
		change_rotation(&fdf->angle.y, ROTATION_STEP * fdf->autorotate.y);
		change_rotation(&fdf->angle.z, ROTATION_STEP * fdf->autorotate.z);
		update_canvas(fdf);
	}
	return (0);
}
