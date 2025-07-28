/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vflorez <vflorez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:48:29 by vrads             #+#    #+#             */
/*   Updated: 2025/07/28 18:21:02 by vflorez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Calculates texture coordinates for wall mapping
 * @param game Pointer to game structure containing player position
 * @param ray Pointer to ray structure with wall data
 *
 * Determines the exact point where the ray hit the wall and calculates
 * the corresponding X coordinate in the texture (0.0 to 1.0).
 */
void	calculate_texture_coordinates(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)game->textures.width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = game->textures.width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = game->textures.width - ray->tex_x - 1;
}

/**
 * @brief Renders a textured vertical wall line on screen
 * @param game Pointer to game structure containing image buffer
 * @param x Screen column to draw on
 * @param ray Pointer to ray structure with drawing parameters
 *
 * Draws a vertical line representing a wall slice using real texture data.
 * Applies proper texture mapping and shading for depth perception.
 */
void	render_textured_wall_line(t_game *game, int x, t_ray *ray)
{
	int		*texture_data;
	int		y;
	int		tex_y;
	int		color;
	double	tex_pos;

	texture_data = get_wall_texture(game, ray->side, ray->dir_x, ray->dir_y);
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * (1.0
			* game->textures.height / ray->line_height);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (game->textures.height - 1);
		tex_pos += (1.0 * game->textures.height / ray->line_height);
		color = get_texture_pixel(texture_data, ray->tex_x, tex_y,
				game->textures.width);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		my_pixel_put(game, x, y, color);
		y++;
	}
}

/**
 * @brief Clears the screen background with sky and floor colors
 * @param game Pointer to game structure containing image data
 *
 * This function fills the screen buffer with sky (upper half) and floor
 * (lower half) colors using only WHILE loops as per Norminette rules.
 */
void	clear_screen_background(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				my_pixel_put(game, x, y, game->map->ceiling_color);
			else
				my_pixel_put(game, x, y, game->map->floor_color);
			x++;
		}
		y++;
	}
}
