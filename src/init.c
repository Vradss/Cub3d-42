/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrads <vrads@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:20:04 by vrads             #+#    #+#             */
/*   Updated: 2025/07/28 14:22:08 by vrads            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_vars(t_game *game)
{
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		exit_error("Error:\nMemory allocation failed");
	game->map->map = NULL;
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->img_data = NULL;
	game->texture = NULL;
	game->zbuffer = NULL;
}

void	my_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error:\nMLX init failed\n");
		return (1);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
	{
		printf("Error:\nWindow creation failed\n");
		return (1);
	}
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->line_len,
			&game->endian);
	return (0);
}
