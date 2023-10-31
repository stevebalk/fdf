/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:29:21 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/31 13:01:40 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Counts elements in one line seperated by space */
int	get_line_elements(t_fdf *fdf, char *line)
{
	int	columns;
	int	found_space;

	if (line[ft_strlen(line) - 1] == '\n')
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
	printf("Column length: %i\n", fdf->map_size.x);
	if (fdf->map_size.x == 0)
		fdf->map_size.x = get_line_elements(fdf, line);
	else if (get_line_elements(fdf, line) != fdf->map_size.x)
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
