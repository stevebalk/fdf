/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:06:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/09/26 14:33:32 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H


/* KEYCODES */

#define ESC		65307

/* COLORS */
#define WHITE	0x00FFFFFF
#define BLACK	0x00000000
#define RED		0x00FF0000
#define GREEN	0x0000FF00
#define BLUE	0x000000FF
#define YELLOW	0x00FFFF00
#define CYAN	0x0000FFFF
#define MAGENTA	0x00FF00FF

/* Structs */

typedef	struct	s_map
{
	int	width;
	int	height;
	int	*coords_arr;
	int	*colors_arr;
	int	z_min;
	int	z_max;
	int	z_range;
}				t_map;

# include "libft.h"
# include "mlx_int.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <errno.h>


#endif
