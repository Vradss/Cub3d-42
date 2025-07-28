/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:18:40 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/28 22:01:54 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * skip_to_map_start - Skips the file until it finds the start of the map.
 * 
 * 1 - Reads and discards lines up to the `target` line index.
 * 2 - Then continues skipping lines that contain only whitespace.
 * 3 - Stops when it finds a non-space, non-empty line (assumed map start).
 * 4 - Returns this line for further processing.
 */
char	*skip_to_map_start(int fd, int target)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (i++ < target)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && is_only_spaces(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

/**
 * valid_char_in_map - Checks if a line contains only valid map characters.
 * 
 * 1 - Returns false immediately if the line is empty or just a newline.
 * 2 - Iterates each character until '\n' or '\0':
 *     - Accepts ' ', '0', '1', 'N', 'S', 'E', 'W' as valid.
 *     - If it's a direction character, checks for duplicate players.
 * 3 - If it encounters an invalid character, exits with an error.
 * 4 - Returns true if the entire line is valid.
 */
int	valid_char_in_map(char *line)
{
	int		i;
	char	letter;

	i = 0;
	if (line[i] == '\n' || line[i] == '\0')
		return (false);
	while (line[i] != '\n' && line[i] != '\0')
	{
		letter = line[i];
		if (letter == ' ' || letter == '0' || letter == '1'
			|| letter == 'N' || letter == 'S' || letter == 'E'
			|| letter == 'W')
		{
			if (check_dup_players(letter, 'N'))
				return (false);
			i++;
		}
		else if (letter == '\0')
			return (true);
		else
			exit_error("Error:\nInvalid character");
	}
	return (true);
}

/**
 * adjust_map_line - Rewrites a map line, replacing spaces and padding.
 * 
 * 1 - Allocates a new string of length `data->line_size`.
 * 2 - Copies characters from the input `content`.
 *     - Spaces are replaced with '1' to treat them as walls.
 * 3 - If the line is shorter than `line_size`, fills remaining space with '1'.
 * 4 - Null-terminates the string and returns it.
 */
char	*adjust_map_line(char *content, t_data *data)
{
	int		i;
	int		content_len;
	char	*line;

	i = -1;
	content_len = data->line_size;
	line = malloc(sizeof(char) * content_len);
	if (line == NULL)
		exit_error("Error:\nMallocation failed");
	while (content[++i] != '\0')
	{
		line[i] = content[i];
		if (content[i] == ' ')
			line[i] = '1';
	}
	while (i < content_len)
	{
		line[i - 1] = '1';
		i++;
	}
	line[content_len - 1] = '\0';
	return (line);
}

/**
 * read_map_lines - Reads and validates each map line from file.
 * 
 * 1 - Iterates over lines, starting from the first provided line.
 * 2 - Validates the line with `valid_char_in_map`; on error, frees and exits.
 * 3 - Saves original line in `backup_map[i]`.
 * 4 - Saves adjusted version in `data->raw_map[i]`.
 * 5 - Frees current line and reads the next using `get_next_line()`.
 * 6 - After all lines, calls `exec_check()` to finish validation.
 * 7 - Returns the result of `exec_check()` (true or false).
 */
int	read_map_lines(t_data *data, int fd, char *line, char **backup_map)
{
	int	i;

	i = 0;
	while (line)
	{
		if (!valid_char_in_map(line))
			return (free_array((void **)backup_map), free(line), false);
		backup_map[i] = ft_strdup(line);
		data->raw_map[i++] = adjust_map_line(line, data);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (exec_check(data, data->game, i, backup_map));
}

/**
 * process_map - Main entry point to process and validate the map.
 * 
 * 1 - Assigns `game` pointer to `data->game`.
 * 2 - Calls `skip_to_map_start()` to locate the actual start of the map
 *     (ignoring metadata and blank lines).
 * 3 - Allocates memory for `raw_map` and `backup_map`.
 *     - Both sized `data->map_length + 1`.
 * 4 - If allocation fails or no valid line is found, frees and returns false.
 * 5 - Calls `read_map_lines()` to validate, process, and populate the map data.
 * 6 - Closes the file descriptor and returns success or failure.
 */
int	process_map(t_data *data, int fd, t_game *game)
{
	char	*line;
	char	**backup_map;

	data->game = game;
	line = skip_to_map_start(fd, data->reading_pos);
	data->raw_map = ft_calloc(data->map_length + 1, sizeof(char *));
	backup_map = ft_calloc(data->map_length + 1, sizeof(char *));
	if (!data->raw_map || !backup_map)
		exit_error("Error:\nMallocation failed");
	if (!line)
		return (free_array((void **)backup_map), close(fd), false);
	if (!read_map_lines(data, fd, line, backup_map))
		return (close(fd), false);
	return (close(fd), true);
}
