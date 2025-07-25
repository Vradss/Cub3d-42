/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:18:13 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/25 21:05:06 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * initializes a `t_data` struct with default values.
 */
void	init_data(t_data *data)
{
	data->raw_map = NULL;
	data->map = NULL;
	data->no = ft_strdup("X");
	data->so = ft_strdup("X");
	data->we = ft_strdup("X");
	data->ea = ft_strdup("X");
	data->f_color[0] = -1;
	data->f_color[1] = -1;
	data->f_color[2] = -1;
	data->c_color[0] = -1;
	data->c_color[1] = -1;
	data->c_color[2] = -1;
	data->reading_pos = 0;
	data->map_length = 0;
	data->line_size = 0;
	data->error = 0;
}

/**
 * Reads a map file with a .cub extension and initializes data for a game.
 * 
 * @param game The `game` parameter is a pointer to a `t_game` struct, 
 * used to store information related to the game state, such as player 
 * position, map data, textures, and other game-related variables. In the 
 * `check_data` function, this `game` parameter is passed.
 * 
 * @return The function `check_data` is returning a variable of type `t_data`.
 */
t_data	check_data(char *argv, t_game *game)
{
	t_data	data;
	int		len;

	len = ft_strlen(argv);
	init_data(&data);
	if (len > 4 && !ft_strcmp(argv + len - 4, ".cub"))
	{
		if (!read_map(argv, &data, game))
		{
			data.error = 1;
			return (data);
		}
	}
	else
	{
		printf("Error:\nNot a .cub file. Use: ./cub3D maps/[map.cub]\n");
		exit(EXIT_FAILURE);
	}
	return (data);
}

/**
 * Parses a single line from the configuration part of the map file (before 
 * the actual map), checks if it's a valid directive, and updates data 
 * accordingly.
 * 
 * 1 - All data already set? If all textures (NO, SO, WE, EA) and both 
 * colors (F, C) are already set, return true (parsing is done).
 * 2 - Normalize the line: normalize_line(line); removes extra spaces for 
 * consistent parsing.
 * 3 - Check for invalid or duplicate attribute: invalid_or_dup_attr() 
 * reports duplicates or bad formatting.
 * 4 - Check texture directives: If line starts with NO , SO , EA , or WE ,
 * call valid_texture_dir(). Return false either way to indicate parsing 
 * continues.
 * 5 - Check color directives: If line starts with F or C , call 
 * valid_color(). Again, return false.
 * 6 - Default: If it matches none of the above, return false.
 * 
 * This function always returns false except when all required attributes 
 * are already set at the beginning — that’s how it signals “parsing is done.”
 */
int	valid_map_line(char *line, t_data *data)
{
	if (ft_strcmp(data->no, "X") && ft_strcmp(data->so, "X")
		&& ft_strcmp(data->we, "X") && ft_strcmp(data->ea, "X")
		&& data->f_color[0] != -1 && data->c_color[0] != -1)
		return (true);
	normalize_line(line);
	invalid_or_dup_attr(line, data);
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0)
	{
		if (!valid_texture_dir(line, data))
			return (false);
		return (false);
	}
	if ((ft_strncmp(line, "F ", 2) == 0) || (ft_strncmp(line, "C ", 2) == 0))
	{
		if (!valid_color(line, data))
			return (false);
		return (false);
	}
	return (false);
}

/** 
 * Reads and parses a map file: first the configuration (textures/colors), 
 * then the actual map layout. Extracts config and map data, validates it,
 * and prepares data and game for use.
 * 
 * 1 - Open file: Opens the map file; exits if it fails.
 * 2 - Read lines: Reads each line using get_next_line():
 * while loop reads line by line until finding a 1st valid line with 
 * `valid_map_line(line, data)` and stops when map content begins.
 * Then tracks reading position (data->reading_pos).
 * 3 - Check attributes: If no map content was found (i.e. line == NULL),
 * exits with error.
 * 4 - Measure map: map_length() determines how many lines the map contains.
 * 5 - Process the map: process_map() handles map validation and setup.
 * 6 - Close the file and return true if successful.
 * */
int	read_map(char *map, t_data *data, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		exit_error("Error:\nUnable to open map");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (valid_map_line(line, data))
			break ;
		data->reading_pos++;
		free(line);
		line = get_next_line(fd);
	}
	if (line == NULL)
		exit_error("Error:\nAttributes missing");
	map_length(line, fd, map, data);
	if (process_map(data, fd, game) == false || data->error)
		exit_error("Error:\nMap is not valid");
	return (close(fd), true);
}
