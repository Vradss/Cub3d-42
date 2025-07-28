/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrads <vrads@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:20:51 by vrads             #+#    #+#             */
/*   Updated: 2025/07/28 10:13:05 by vrads            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Loads a single texture from XPM file
 * @param game Pointer to game structure containing MLX instance
 * @param texture_path Path to the XPM texture file
 * @param texture_img Pointer to store the loaded texture image
 * @param texture_data Pointer to store the texture pixel data
 * @return 1 on success, 0 on failure
 *
 * Uses mlx_xpm_file_to_image to load texture and mlx_get_data_addr
 * to get pixel data for direct access during rendering.
 */
static int	load_single_texture(t_game *game, char *texture_path,
		void **texture_img, int **texture_data)
{
	int	width;
	int	height;
	int	bpp;
	int	line_len;
	int	endian;

	*texture_img = mlx_xpm_file_to_image(game->mlx, texture_path, &width,
			&height);
	if (!*texture_img)
	{
		printf("Error: Failed to load texture: %s\n", texture_path);
		return (0);
	}
	*texture_data = (int *)mlx_get_data_addr(*texture_img, &bpp, &line_len,
			&endian);
	if (!*texture_data)
	{
		printf("Error: Failed to get texture data: %s\n", texture_path);
		return (0);
	}
	return (1);
}

/**
 * @brief Loads all four wall textures from parsed data
 * @param game Pointer to game structure
 * @param data Pointer to parsed data containing texture paths
 * @return 1 on success, 0 on failure
 *
 * Loads North, South, West, and East textures using the paths
 * stored in the parsing data structure. Sets texture dimensions
 * assuming all textures are 64x64 pixels.
 */
int	load_wall_textures(t_game *game, t_data *data)
{
	if (!load_single_texture(game, data->no, &game->textures.north,
			&game->textures.north_data))
		return (0);
	if (!load_single_texture(game, data->so, &game->textures.south,
			&game->textures.south_data))
		return (0);
	if (!load_single_texture(game, data->we, &game->textures.west,
			&game->textures.west_data))
		return (0);
	if (!load_single_texture(game, data->ea, &game->textures.east,
			&game->textures.east_data))
		return (0);
	game->textures.width = 64;
	game->textures.height = 64;
	return (1);
}

/**
 * @brief Gets a specific pixel color from texture data
 * @param texture_data Pointer to texture pixel data array
 * @param x X coordinate in texture (0-63)
 * @param y Y coordinate in texture (0-63)
 * @param tex_width Width of texture in pixels
 * @return Integer color value in RGB format
 *
 * Safely retrieves pixel color from texture data with bounds checking.
 * Assumes texture is square and uses standard indexing formula.
 */
int	get_texture_pixel(int *texture_data, int x, int y, int tex_width)
{
	if (x < 0 || x >= tex_width || y < 0 || y >= tex_width)
		return (0x000000);
	return (texture_data[y * tex_width + x]);
}

/**
 * @brief Determines which texture to use based on wall side and direction
 * @param game Pointer to game structure containing loaded textures
 * @param side Wall side (0 for NS walls, 1 for EW walls)
 * @param ray_dir_x X component of ray direction
 * @param ray_dir_y Y component of ray direction
 * @return Pointer to appropriate texture data
 *
 * Selects correct texture based on which side of wall was hit:
 * - North wall: ray hitting from south (ray_dir_y > 0)
 * - South wall: ray hitting from north (ray_dir_y < 0)
 * - West wall: ray hitting from east (ray_dir_x > 0)
 * - East wall: ray hitting from west (ray_dir_x < 0)
 */
int	*get_wall_texture(t_game *game, int side, double ray_dir_x,
		double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (game->textures.west_data);
		else
			return (game->textures.east_data);
	}
	else
	{
		if (ray_dir_y > 0)
			return (game->textures.north_data);
		else
			return (game->textures.south_data);
	}
}

void	convert_colors_to_int(t_game *game, t_data *data)
{
	game->map->floor_color = (data->f_color[0] << 16) | (data->f_color[1] << 8) | data->f_color[2];

	game->map->ceiling_color = (data->c_color[0] << 16) | (data->c_color[1] << 8) | data->c_color[2];
}
