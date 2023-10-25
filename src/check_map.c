/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:29:21 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/25 01:01:03 by sbalk            ###   ########.fr       */
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

/* Counts elements in one line seperated by space */
int	get_column_length(t_fdf *fdf, char *line)
{
	int	columns;
	int	found_space;

	line[ft_strlen(line) - 1] = '\0';
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
	{
		free(line);
		error_msg(fdf, "Error: Empty line", 1, 1);
	}
	return (columns);
}

/* Set newline character to null character and check
if line is correctly formated */
void	line_check(t_fdf *fdf, char *line)
{
	if (fdf->map_size.x == 0)
		fdf->map_size.x = get_column_length(fdf, line);
	else if (get_column_length(fdf, line) != fdf->map_size.x)
	{
		free(line);
		error_msg(fdf, "Error: Wrong line length.", 1, 1);
	}
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
	while (line)
	{
		fdf->map_size.y++;
		line_check(fdf, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (fdf->map_size.y == 0)
		error_msg(fdf, "Error: Empty Map.", 0, 1);
}
