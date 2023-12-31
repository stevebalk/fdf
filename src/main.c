/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:41:41 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/01 15:41:00 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_fdf	fdf;

	if (argc != 2)
	{
		ft_printf("Wrong number of arguments.\n");
		ft_printf("Use: ./fdf <mapfile>\n");
		exit(1);
	}
	init_fdf(&fdf);
	check_map_format(&fdf, argv[1]);
	init_maps(&fdf);
	read_map(&fdf, argv[1]);
	init_mlx(&fdf);
	init_iso_projection(&fdf);
	update_canvas(&fdf);
	init_keyhooks(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
