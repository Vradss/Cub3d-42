/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:16:27 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/25 20:36:14 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
			if (map[x_y[0]][x_y[1]] == 'S' || map[x_y[0]][x_y[1]] == 'N' ||
				map[x_y[0]][x_y[1]] == 'E' || map[x_y[0]][x_y[1]] == 'W')
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
				game->player.dir_x = 0;
				game->player.dir_y = -1;
				init_pos_player(game, map, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

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
