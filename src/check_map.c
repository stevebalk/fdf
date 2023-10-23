/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:29:21 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/23 19:52:12 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Checks file integrity */
void	check_file_integrity(t_fdf *fdf, char *filename)
{
	if (access(filename, F_OK) == -1)
		error_msg(fdf, "Error: File does not exist", 1, 1);
	if (access(filename, R_OK) == -1)
		error_msg(fdf, "Error: No read permission", 1, 1);
}

int	get_column_length(t_fdf *fdf, char *line)
{
	int	columns;
	int	found_space;

	columns = 0;
	found_space = 1;
	while (*line)
	{
		if (*line != ' ' && found_space)
		{
			columns++;
			found_space = 0;
		}
		else if (*line == ' ')
			found_space = 1;
		line++;
	}
	ft_printf("Columns: %i\n", columns);
	if (columns == 0)
		error_msg(fdf, "Error: Empty line", 0, 1);
	return (columns);
}

int	is_line_correct(t_fdf *fdf, char *line)
{
	line[ft_strlen(line) - 1] = '\0';
	if (get_column_length(fdf, line) != fdf->map_size.x)
		return (0);
	return (1);
}

/* Read the mapfile and check if it's in the correct format*/
void	check_map_format(t_fdf *fdf, char *filename)
{
	char	*line;
	int		fd;

	check_file_integrity(fdf, filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_msg(fdf, "Error: Opening file.", 1, 1);
	line = get_next_line(fd);
	if (line)
		fdf-> map_size.x = get_column_length(fdf, line);
	while (line)
	{
		fdf->map_size.y++;
		if (!is_line_correct(fdf, line))
		{
			free(line);
			error_msg(fdf, "Error: Wrong line length.", 1, 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (fdf->map_size.y == 0)
		error_msg(fdf, "Error: Empty Map.", 0, 1);
}
