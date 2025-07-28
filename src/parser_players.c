/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:16:27 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/28 22:05:30 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * check_dup_players - Tracks and validates the number of player directions.
 * 
 * 1 - Uses static counters for each direction (N, S, E, W).
 * 2 - Increments the counter matching the given `letter`.
 * 3 - If any direction exceeds 1, exits with "duplicated player" error.
 * 4 - If `yes_or_no` is 'Y', does a final check:
 *     - If sum is 0, exits with "no player found".
 *     - If sum > 1, exits with "multiple players not allowed".
 * 5 - Always returns false (used only for validation logic).
 */
int	check_dup_players(char letter, char yes_or_no)
{
	static int	n = 0;
	static int	s = 0;
	static int	e = 0;
	static int	w = 0;
	int			sum;

	if (letter == 'N')
		n++;
	else if (letter == 'S')
		s++;
	else if (letter == 'E')
		e++;
	else if (letter == 'W')
		w++;
	if (n > 1 || s > 1 || e > 1 || w > 1)
		exit_error("Error:\nDuplicated player");
	if (yes_or_no == 'Y')
	{
		sum = n + s + e + w;
		if (sum == 0)
			exit_error("Error:\nNo player found");
		if (sum > 1)
			exit_error("Error:\nMultiple players not allowed");
	}
	return (false);
}

/**
 * check_all_closed - Recursively checks if a region is surrounded by walls.
 * 
 * 1 - Stops and returns false if position is out of bounds.
 * 2 - If cell is '1' or ' ', considers it closed and returns true.
 * 3 - Marks the current cell as '1' to avoid revisiting it.
 * 4 - Recursively checks all 4 directions (up, down, left, right).
 * 5 - Combines all checks with AND to ensure complete enclosure.
 * 6 - Returns true if all directions are properly enclosed.
 */
static bool	check_all_closed(int x, int y, char **map, int size)
{
	bool	is_closed;

	if (y < 0 || y >= size || x < 0 || x >= (int)ft_strlen(map[y]))
		return (false);
	if (map[y][x] == '1' || map[y][x] == ' ')
		return (true);
	map[y][x] = '1';
	is_closed = true;
	is_closed &= check_all_closed(x, y - 1, map, size);
	is_closed &= check_all_closed(x, y + 1, map, size);
	is_closed &= check_all_closed(x - 1, y, map, size);
	is_closed &= check_all_closed(x + 1, y, map, size);
	return (is_closed);
}

/**
 * check_player_in_walls - Ensures player is within a closed wall area.
 * 
 * 1 - Scans the map to find the first player character (N, S, E, W).
 * 2 - Stores the (x, y) position of the player.
 * 3 - If no player is found, returns false.
 * 4 - Calls `check_all_closed()` to verify the surrounding area is enclosed.
 * 5 - Returns the result of that check.
 */
bool	check_player_in_walls(char **map, int size)
{
	int	player[2];
	int	x_y[2];

	player[0] = -1;
	player[1] = -1;
	x_y[0] = 0;
	x_y[1] = 0;
	while (x_y[0] < size && player[0] == -1)
	{
		x_y[1] = 0;
		while (x_y[1] < (int)ft_strlen(map[x_y[0]]) && player[0] == -1)
		{
			if (map[x_y[0]][x_y[1]] == 'S' || map[x_y[0]][x_y[1]] == 'N'
				|| map[x_y[0]][x_y[1]] == 'E' || map[x_y[0]][x_y[1]] == 'W')
			{
				player[0] = x_y[1];
				player[1] = x_y[0];
			}
			x_y[1]++;
		}
		x_y[0]++;
	}
	if (player[0] == -1)
		return (false);
	return (check_all_closed(player[0], player[1], map, size));
}

/**
 * get_player_position - Locates the player and initializes position data.
 * 
 * 1 - Iterates over each row and column of the map.
 * 2 - Looks for the first occurrence of 'N', 'E', 'S', or 'W'.
 * 3 - Sets `game->player.x` and `game->player.y` to the center of that cell.
 * 4 - Calls `init_pos_player()` to set direction and plane based on symbol.
 * 5 - Returns immediately after first match (only one player expected).
 */
void	get_player_position(char **map, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\n' && map[y][x] != '\0')
		{
			if (ft_strchr("NESW", map[y][x]) != NULL)
			{
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				init_pos_player(game, map, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

/**
 * init_pos_player - Sets the player's direction and camera plane.
 * 
 * 1 - Reads the player's orientation character from the map.
 * 2 - Initializes `plane_x` and `plane_y` with default camera plane values.
 * 3 - Based on the direction:
 *     - 'N' -> Facing up (dir_y = -1)
 *     - 'S' -> Facing down (dir_y = 1)
 *     - 'E' -> Facing right (dir_x = 1)
 *     - 'W' -> Facing left (dir_x = -1)
 * 4 - Sets the directional vector accordingly.
 */

void	init_pos_player(t_game *game, char **map, int x, int y)
{
	char	pos;

	pos = map[y][x];
	game->player.plane_x = FOV;
	game->player.plane_y = 0.0;
	if (pos == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (pos == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (pos == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else if (pos == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
}
