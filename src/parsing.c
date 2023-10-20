/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:37:15 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/19 17:06:22 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hex_to_int(t_fdf *fdf, char *hex_string)
{
    int result = 0;
	int i;

	result = 0;
	i = 0;
	while (hex_string[i] != '\0')
	{
		result = result * 16;
		if (hex_string[i] >= '0' && hexString[i] <= '9')
            result += hex_string[i] - '0';
		else if (hex_string[i] >= 'A' && hex_string[i] <= 'F')
            result += hex_string[i] - 'A' + 10;
        else if (hex_string[i] >= 'a' && hex_string[i] <= 'f')
            result += hex_string[i] - 'a' + 10;
        else
            return 0;
		i++;
	}
    return result;
}

int	parse_color(t_fdf *fdf, char *str)
{
	int	len;
	int	i;

	len = strlen(str);
	i = 0;
	if (!(len >= 2 && len <= 8 && len % 2 == 0))
		return (fdf->default_color);
	while (str[i])
	{
		if (ft_strchr(HEXALOW, str[i]))
			i++;
		else if (ft_strchr(HEXAUP, str[i]))
			i++;
		else
			return (fdf->default_color);
	}
	return (hex_to_int(fdf, str));
}

/* Parse one chunk, like 2,0xFF45F500 */
t_vert3d	*parse_chunk(t_fdf *fdf, char *chunk, int row, int column)
{
	char		*str;
	t_vert3d	*vert;

	vert = malloc(sizeof(t_vert3d));
	vert->color = fdf->default_color;
	vert->pos.z = ft_atoi(chunk);
	str = chunk;
	while (ft_is_space(*str) && *str == '-' && *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '\0' || !ft_strncmp(str, ",0x", 3) == 0)
		vert->color = fdf->default_color;
	else
		vert->color = parse_color(fdf, str + 3);
	return (vert);
}

/* Returns element count of the line */
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
	fdf->map[row] = malloc(size * sizeof(t_vert3d));
	while (i < size)
	{

	}

}


/* Read the mapfile and check if it's in the correct format*/
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