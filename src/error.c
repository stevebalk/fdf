/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:33:06 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/23 17:37:17 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(t_fdf *fdf)
{
	ft_free_array((void **) fdf->input_map);
	ft_free_array((void **) fdf->map);
}

void	error_msg(t_fdf *fdf, char *msg, int use_errno, int shall_exit)
{
	ft_putendl_fd(msg, 2);
	if (shall_exit)
	{
		free_fdf(fdf);
		if (use_errno)
			exit(errno);
		exit(EXIT_FAILURE);
	}
}
