/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrads <vrads@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:07:03 by vrads             #+#    #+#             */
/*   Updated: 2025/07/24 14:44:22 by vrads            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Checks for collision at specified coordinates
 * @param map 2D character array representing the game map
 * @param x X coordinate to check for collision
 * @param y Y coordinate to check for collision
 * @return 1 if collision detected (wall or boundary), 0 if clear
 *
 * Performs boundary checking and wall detection at given coordinates.
 * Returns collision if position is outside map bounds or contains a wall ('1').
 */
int	check_collision(char **map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || !map[map_y] || !map[map_y][map_x])
		return (1);
	return (map[map_y][map_x] == '1');
}

/**
 * @brief Moves player forward in their current facing direction
 * @param game Pointer to game structure containing player data
 * @param map 2D character array for collision detection
 *

	* Calculates new position based on player's direction vector and movement speed.
 * Performs collision detection separately for X and Y axes to allow sliding
 * along walls. Only updates position if no collision is detected.
 */
void	move_forward(t_game *game, char **map)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (!check_collision(map, new_x, game->player.y))
		game->player.x = new_x;
	if (!check_collision(map, game->player.x, new_y))
		game->player.y = new_y;
}
/**
 * @brief Moves player backward (opposite to their facing direction)
 * @param game Pointer to game structure containing player data
 * @param map 2D character array for collision detection
 *
 * Calculates new position by moving in the opposite direction of the player's
 * direction vector. Uses separate collision detection for each axis to enable
 * smooth wall sliding behavior.
 */
void	move_backward(t_game *game, char **map)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (!check_collision(map, new_x, game->player.y))
		game->player.x = new_x;
	if (!check_collision(map, game->player.x, new_y))
		game->player.y = new_y;
}
/**
 * @brief Moves player left (perpendicular to facing direction)
 * @param game Pointer to game structure containing player data
 * @param map 2D character array for collision detection
 *
 * Performs strafing movement using the camera plane vector which is
 * perpendicular to the direction vector. Enables sideways movement
 * without changing the player's viewing direction.
 */
void	strafe_left(t_game *game, char **map)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
	if (!check_collision(map, new_x, game->player.y))
		game->player.x = new_x;
	if (!check_collision(map, game->player.x, new_y))
		game->player.y = new_y;
}
/**
 * @brief Moves player right (perpendicular to facing direction)
 * @param game Pointer to game structure containing player data
 * @param map 2D character array for collision detection
 *
 * Performs strafing movement in the positive direction of the camera plane
 * vector. Allows sideways movement while maintaining the current viewing
 * angle and direction.
 */
void	strafe_right(t_game *game, char **map)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
	if (!check_collision(map, new_x, game->player.y))
		game->player.x = new_x;
	if (!check_collision(map, game->player.x, new_y))
		game->player.y = new_y;
}
/**
 * @brief Rotates player view to the left (counterclockwise)
 * @param game Pointer to game structure containing player data
 *
 * Applies 2D rotation matrix to both direction and camera plane vectors
 * using the rotation speed constant. Updates both dir_x/dir_y and
 * plane_x/plane_y to maintain proper perspective projection.
 */
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(ROT_SPEED)
		- game->player.dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y
		* cos(ROT_SPEED);
	game->player.plane_x = game->player.plane_x * cos(ROT_SPEED)
		- game->player.plane_y * sin(ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y
		* cos(ROT_SPEED);
}
/**
 * @brief Rotates player view to the right (clockwise)
 * @param game Pointer to game structure containing player data
 *
 * Applies 2D rotation matrix with negative rotation speed to rotate
 * clockwise. Updates both direction and camera plane vectors simultaneously
 * to ensure consistent raycasting perspective.
 */
void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED)
		- game->player.dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y
		* cos(-ROT_SPEED);
	game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED)
		- game->player.plane_y * sin(-ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y
		* cos(-ROT_SPEED);
}
