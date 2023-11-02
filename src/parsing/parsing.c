/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:37:15 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/02 12:50:50 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Transforms hex to int value, return -1 if invalid hex value*/
static int	hex_to_int(char *hex_string)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (hex_string[i] != '\0')
	{
		result = result * 16;
		if (hex_string[i] >= '0' && hex_string[i] <= '9')
			result += hex_string[i] - '0';
		else if (hex_string[i] >= 'A' && hex_string[i] <= 'F')
			result += hex_string[i] - 'A' + 10;
		else if (hex_string[i] >= 'a' && hex_string[i] <= 'f')
			result += hex_string[i] - 'a' + 10;
		else
			return (-1);
		i++;
	}
	return (result);
}

/* Parse color, for example "0xFFBBDDFF" */
static int	parse_color(t_fdf *fdf, char *str)
{
	int	color;
	int	i;

	i = 0;
	while ((str[i] >= '0' && str[i] <= '9')
		|| (str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] >= 'A' && str[i] <= 'Z'))
		i++;
	str[i] = '\0';
	color = hex_to_int(str);
	if (color == -1)
		return (fdf->default_color);
	return (color);
}

/* Parse one chunk, for example "2,0xFFFF00" */
static t_vert3d	parse_chunk(t_fdf *fdf, char *chunk, int row, int column)
{
	char		*str;
	t_vert3d	vert;

	vert.pos.x = column - fdf->pivot.x;
	vert.pos.y = row - fdf->pivot.y;
	vert.pos.z = ft_atoi(chunk);
	vert.changeable = 0;
	if (vert.pos.z != 0.0)
		vert.changeable = 1;
	str = chunk;
	while (*str == ' ' || *str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '\0' || !(ft_strncmp(str, ",0x", 3) == 0))
		vert.color = fdf->default_color;
	else
		vert.color = parse_color(fdf, str + 3);
	return (vert);
}

/* Parse one line */
static void	parse_line(t_fdf *fdf, char *line, int row)
{
	char	**chunks;
	int		size;
	int		i;

	size = fdf->map_size.x;
	i = 0;
	chunks = ft_split(line, ' ');
	if (chunks == NULL)
		error_msg(fdf, "Error: ft_split failed", 1, 1);
	while (i < size)
	{
		fdf->input_map[row][i] = parse_chunk(fdf, chunks[i], row, i);
		fdf->map[row][i].color = fdf->input_map[row][i].color;
		i++;
	}
	ft_free_array((void **) chunks);
}

/* Read the mapfile and check if it's in the correct format*/
void	read_map(t_fdf *fdf, char *filename)
{
	int		row;
	int		fd;
	char	*line;

	row = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_msg(fdf, "Error: Could not open file", 1, 1);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(fdf, line, row);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
	set_altitude_color(fdf);
}
