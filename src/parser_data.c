/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:18:13 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/24 20:46:30 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

/* while loop reads line by line until finding a 1st valid line
with `valid_map_line(line, data)`*/
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
