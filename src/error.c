/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:33:06 by sbalk             #+#    #+#             */
/*   Updated: 2023/09/28 16:19:26 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(t_fdf *fdf)
{
	ft_free_array((void *) fdf->final_points);
	ft_free_array((void *) fdf->input_points);
}

void	error_msg(t_fdf *fdf, char *msg, int shall_exit)
{
	ft_putendl_fd(msg, 2);
	if (shall_exit)
	{
		free_fdf(fdf);
		exit(errno);
	}
}

