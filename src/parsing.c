/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:37:15 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/20 19:00:28 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hex_to_int(char *hex_string)
{
	int result;
	int i;

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
	return result;
}

int	parse_color(t_fdf *fdf, char *str)
{
	int	len;
	int	i;
	int	color;

	len = strlen(str);
	i = 0;
	if (!(len >= 2 && len <= 8 && len % 2 == 0))
		return (fdf->default_color);
	color = hex_to_int(str);
	if (color == -1)
		return (fdf->default_color);
	return (color);
}

/* Parse one chunk, like 2,0xFF45F500 */
t_vert3d	*parse_chunk(t_fdf *fdf, char *chunk, int row, int column)
{
	char		*str;
	t_vert3d	*vert;

	vert = malloc(sizeof(t_vert3d));
	vert->pos.x = column;
	vert->pos.y = row;
	vert->pos.z = ft_atoi(chunk);
	str = chunk;
	while (ft_is_space(str) || *str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '\0' || !ft_strncmp(str, ",0x", 3) == 0)
		vert->color = fdf->default_color;
	else
		vert->color = parse_color(fdf, str + 3);
	return (vert);
}

/* Returns pointer to column array */
void	**parse_line(t_fdf *fdf, char *line, int row)
{
	char	**chunks;
	size_t	size;
	size_t	i;

	i = 0;
	size = count_columns(fdf, line);
	if (size != fdf->map_size.x)
		error_msg(fdf, "Map" , "Wrong line length. Exiting.", 1);
	chunks = ft_split(line, ' ');
	if (chunks == NULL)
		error_msg(fdf, "parse line", "ft_split", 1);
	fdf->input_map[row] = malloc(size * sizeof(t_vert3d));
	chunks[size - 1][ft_strlen(chunks[size -1]) - 1] = '\0';
	while (i < size)
	{
		fdf->input_map[row][i] = parse_chunk(fdf, chunks[i], row, i);
		i++;
	}
	ft_free_array(chunks);
}

/* Checks file integrity */
void	check_file_integrity(t_fdf *fdf, char *filename, char *func_name)
{
	if (access(filename, F_OK) == -1)
		error_msg(fdf, func_name, "File does not exist", 1);
	if (access(filename, R_OK) == -1)
		error_msg(fdf, func_name, "File no read permission", 1);
}

int	count_columns(t_fdf *fdf, char *line)
{
	int	columns;
	int	found_space;

	columns = 0;
	found_space = 1;
	while (*line)
	{
		if (!ft_is_space(line) && found_space)
		{
			columns++;
			found_space = 0;
		}
		else if (ft_is_space(line))
			found_space = 1;
		line++;
	}
	if (columns == 0)
		error_msg(fdf, "count_columns", "0 columns", 1);
	return (columns);
}

/* Count the rows of the map */
void	count_lines(t_fdf *fdf, char *filename)
{
	char	*line;
	int		fd;

	check_file_integrity(fdf, filename, "count_lines");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_msg(fdf, "count_lines", "Open", 1);
	line = get_next_line(fd);
	if (line)
		fdf-> map_size.x = count_columns(fdf, line);
	while (line)
	{
		fdf->map_size.y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (fdf->map_size.y == 0)
		error_msg(fdf, "count_lines", "Empty File", 1);
}

void	fill_rows(t_fdf *fdf, char *filename)
{
	int		row;
	int		fd;
	char	*line;

	row = 0;
	fdf->input_map = malloc(sizeof(t_vert3d *) * fdf->map_size.y);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_msg(fdf, "count_lines", "Open", 1);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(fdf, line, row);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
}

/* Read the mapfile and check if it's in the correct format*/
void read_map(t_fdf *fdf, char *filename)
{
	count_lines(fdf, filename);
	fill_rows(fdf, filename);
}