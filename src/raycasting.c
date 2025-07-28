/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrads <vrads@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:06:42 by vrads             #+#    #+#             */
/*   Updated: 2025/07/28 11:50:30 by vrads            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Initializes ray direction and DDA algorithm variables
 * @param game Pointer to game structure containing player data
 * @param x Current screen column being processed
 * @param ray Pointer to ray structure to initialize
 *
 * Calculates the ray direction based on player position and camera plane.
 * Sets up initial DDA variables for wall detection algorithm.
 */
static void	init_ray_data(t_game *game, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}
/**
 * @brief Calculates step direction and initial side distances for DDA
 * @param game Pointer to game structure containing player position
 * @param ray Pointer to ray structure with direction data
 *
 * Determines which direction to step in (positive or negative) and calculates
 * the initial distances to the next grid lines in both X and Y directions.
 */
static void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

/**
 * @brief Performs DDA algorithm to detect wall collision
 * @param map 2D character array representing the game map
 * @param ray Pointer to ray structure containing DDA variables
 *
 * Uses Digital Differential Analyzer algorithm to step through the grid
 * until a wall ('1') is hit. Updates ray position and side information.
 */
static void	perform_dda_algorithm(char **map, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

/**
 * @brief Calculates perpendicular wall distance and line height
 * @param game Pointer to game structure containing player position
 * @param ray Pointer to ray structure with collision data
 *
 * Computes the perpendicular distance to avoid fisheye effect and
 * calculates the height of the wall line to be drawn on screen.
 */
static void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x)
				/ 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y)
				/ 2) / ray->dir_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

/**
 * @brief Main raycasting function that renders the 3D textured view
 * @param game Pointer to game structure containing all game data
 * @param map 2D character array representing the game map
 *
 * This is the main raycasting loop that:
 * 1. Clears the background with sky and floor
 * 2. Casts a ray for each screen column
 * 3. Detects walls using DDA algorithm
 * 4. Calculates wall distances and texture coordinates
 * 5. Renders textured vertical wall lines to create 3D effect
 */
void	real_raycasting(t_game *game, char **map)
{
	int		x;
	t_ray	ray;

	clear_screen_background(game);
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray_data(game, x, &ray);
		calculate_step_and_side_dist(game, &ray);
		perform_dda_algorithm(map, &ray);
		calculate_wall_distance(game, &ray);
		calculate_texture_coordinates(game, &ray);
		render_textured_wall_line(game, x, &ray);
		x++;
	}
}
