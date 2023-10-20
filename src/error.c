/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:33:06 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/20 18:21:30 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(t_fdf *fdf)
{
	ft_free_2darray((void *) fdf->input_map);
	ft_free_array((void *) fdf->map);
}

void	error_msg(t_fdf *fdf, char *func_name, char *msg, int shall_exit)
{
	
	ft_putendl_fd(func_name, 2);
	ft_putendl_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	ft_putendl_fd(": ", 2);
	if (shall_exit)
	{
		free_fdf(fdf);
		exit(errno);
	}
}

