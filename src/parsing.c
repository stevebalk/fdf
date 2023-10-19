/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:37:15 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/11 17:24:34 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vert3d	parse_chunk(t_fdf *fdf, char *chunk, int row, int column)
{
	char		*str;
	t_vert3d	*vert;

	vert = malloc(sizeof(t_vert3d));
	vert->color = fdf->default_color;
	vert->pos.z = ft_atoi(chunk);
	str = chunk;
	while (ft_is_space(*str))
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '\0')
	{
		
	}
}

/* Returns elements count of the line */
int	parse_line(t_fdf *fdf, char *line, int row)
{
	char	**chunks;
	size_t	size;
	size_t	i;

	size = 0;
	chunks = ft_split(line, ' ');
	if (chunks == NULL)
		error_msg(fdf, "parse line: ft_split", 1);
	while (chunks[size] != NULL)
	{
		size++;
	}
	fdf->final_points[row] = malloc(size * sizeof(t_vert2d));
	while (i < size)
	{

	}

}

void read_map(t_fdf *fdf, char *filename)
{
	char	*line;
	int		fd;
	int		row;

	row = 0;
	if (access(filename, F_OK | R_OK) == -1)
		error_msg(fdf, "Mapfile: ", 1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_msg(fdf, "Open: ", 1);
	line = get_next_line(fd);
	if (line == -1)
		error_msg(fdf, "Empty file!\n", 1);
	fdf->map_size.x = parse_line(fdf, line, row);
	fdf->map_size.y++;
	while (line != -1)
	{
		line = get_next_line(fd);
		if (parse_line(fdf, line, row) != fdf->map_size.x)
			error_msg(fdf, "Map: Wrong number of elements!", 1);
		fdf->map_size.y++;
		row++;
	}
}