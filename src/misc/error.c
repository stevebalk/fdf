/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:33:06 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/29 20:47:39 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
