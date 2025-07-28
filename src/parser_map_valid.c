/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:18:27 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/28 21:54:56 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Initializes the final map structure once all lines have been read and 
 * performs integrity checks.
 * 
 * 1 - Null-terminate the raw_map: `data->raw_map[i] = NULL`.
 * 2 - Allocate `game->map` if not already done. Exit on malloc failure.
 * 3 - Check for duplicate player positions using `check_dup_players()`.
 *     If found, return false.
 * 4 - Store player position via `get_player_position()`.
 * 5 - Loop through `raw_map` to detect empty lines *inside* the map block
 *     (i.e., after content has started). If so, it's invalid — exit error.
 * 6 - Assign raw_map to both `game->map->map` and `data->map`.
 * 7 - Return true to confirm successful map setup.
 */
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

/**
 * Final validation and setup before accepting the map as valid.
 * 
 * 1 - Null-terminate the backup_map (copy of the raw map input).
 * 2 - Check map size:
 *     - Line length max 40 characters & lines must not exceed 20.
 *     - If violated, free memory and return false.
 * 3 - Call `check_n_init_map()` to perform player and empty line checks.
 *     - If any issue, free memory and return false.
 * 4 - Validate walls with `check_player_in_walls()` (ensure player not 
 *     placed near unclosed space). If fails, free and return false.
 * 5 - Ensure the last line of the map is not empty or just a newline.
 *     If it is, the map is invalid — free and return false.
 * 6 - If all checks pass, free `backup_map` and return true.
 */
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
