/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:18:27 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/24 20:24:43 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_n_init_map(t_data *data, int i, t_game *game)
{
	int	pos;
	int	flag;

	pos = 0;
	flag = 0;
	data->raw_map[i] = NULL;
	if (!game->map)
		game->map = malloc(sizeof(t_map));
	if (!game->map)
		exit_error("Error:\nMallocation failed");
	if (check_dup_players(' ', 'Y'))
		return (false);
	get_player_position(data->raw_map, game);
	while (data->raw_map[pos])
	{
		if (data->raw_map[pos][0] == '\n')
			flag = 1;
		else if (data->raw_map[pos][0] != '\n'
			&& data->raw_map[pos][0] != '\0' && flag)
			exit_error("Error:\nInvalid line inside map");
		pos++;
	}
	game->map->map = data->raw_map;
	data->map = data->raw_map;
	return (true);
}

bool	exec_check(t_data *data, t_game *game, int i, char **backup_map)
{
	int	pos;

	backup_map[i] = NULL;
	pos = 0;
	while (backup_map[pos])
	{
		if (ft_strlen(backup_map[pos]) > 40 || pos >= 20)
			return (free_array((void **)backup_map), false);
		pos++;
	}
	if (!check_n_init_map(data, i, game))
		return (free_array((void **)backup_map), false);
	if (!check_player_in_walls(backup_map, data->map_length))
		return (free_array((void **)backup_map), false);
	if (backup_map[i - 1][0] == '\0' || backup_map[i - 1][0] == '\n')
		return (free_array((void **)backup_map), false);
	free_array((void **)backup_map);
	return (true);
}
