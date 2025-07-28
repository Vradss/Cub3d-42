/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:18:40 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/24 20:47:10 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	line[content_len -1] = '\0';
	return (line);
}

/* Reads the map lines, validates, stores them in data->raw_map and backup_map*/
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
