/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:18:53 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/24 19:56:55 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	file_is_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		exit_error("Error:\nImpossible to open file\n");
		return (false);
	}
	close (fd);
	return (true);
}

void	map_length(char *line, int fd, char *map, t_data *data)
{
	size_t	length_line;

	while (line != NULL && is_only_spaces(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		length_line = ft_strlen(line);
		if (length_line > data->line_size)
			data->line_size = length_line;
		data->map_length++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(map, O_RDONLY);
}

int	is_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\v'
				|| line[i] == '\r' || line[i] == '\n' || line[i] == '\f'))
			return (false);
		i++;
	}
	return (true);
}
