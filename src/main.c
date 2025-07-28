/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrads <vrads@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:48:20 by vrads             #+#    #+#             */
/*   Updated: 2025/07/28 10:12:45 by vrads            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_frame(t_data *data)
{
	real_raycasting(data->game, data->map);
	mlx_put_image_to_window(data->game->mlx, data->game->win, data->game->img,
		0, 0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		exit(0);
	else if (keycode == W_KEY)
		move_forward(data->game, data->map);
	else if (keycode == S_KEY)
		move_backward(data->game, data->map);
	else if (keycode == A_KEY)
		strafe_left(data->game, data->map);
	else if (keycode == D_KEY)
		strafe_right(data->game, data->map);
	else if (keycode == LEFT_ARROW)
		rotate_left(data->game);
	else if (keycode == RIGHT_ARROW)
		rotate_right(data->game);
	else
		return (0);
	render_frame(data);
	return (0);
}

void	init_vars(t_game *game)
{
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = FOV;
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

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error: MLX init failed\n");
		return (1);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D test");
	if (!game->win)
	{
		printf("Error: Window creation failed\n");
		return (1);
	}
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->line_len,
			&game->endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game = {0};
	t_data	data;

	if (argc != 2)
	{
		printf("Error:\nWrong nb of args. Use: ./cub3D maps/[map.cub]\n");
		exit(EXIT_FAILURE);
	}
	init_vars(&game);
	data = check_data(argv[1], &game);
	if (data.error)
		return (printf("Error: parsing failed"), 1);
	convert_colors_to_int(&game, &data);
	if (!data.map)
		return (printf("Error: Map not loaded correctly\n"), 1);
	if (init_mlx(&game) != 0)
		return (1);
	if (!load_wall_textures(&game, &data))
		return (printf("Error: Failed to load textures\n"), 1);
	data.game = &game;
	render_frame(&data);
	mlx_hook(game.win, 2, 1L << 0, key_hook, &data);
	mlx_loop(game.mlx);
	printf("✅ Program finished successfully\n");
	return (0);
}
