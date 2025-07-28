/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vflorez <vflorez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:48:20 by vrads             #+#    #+#             */
/*   Updated: 2025/07/28 18:17:38 by vflorez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	render_frame(t_data *data)
{
	real_raycasting(data->game, data->map);
	mlx_put_image_to_window(data->game->mlx, data->game->win, data->game->img,
		0, 0);
	return (0);
}

void	setup_hooks(t_game game, t_data data)
{
	mlx_hook(game.win, 2, 1L << 0, key_hook, &data);
	mlx_hook(game.win, 17, 0, close_window_hook, &data);
	mlx_loop(game.mlx);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		cleanup_and_exit(data);
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

int	main(int argc, char **argv)
{
	t_game	game;
	t_data	data;

	game = (t_game){0};
	if (argc != 2)
	{
		printf("Error:\nWrong nb of args. Use: ./cub3D maps/[map.cub]\n");
		exit(EXIT_FAILURE);
	}
	init_vars(&game);
	data = check_data(argv[1], &game);
	if (data.error || !data.raw_map)
		return (printf("Error:\nParsing failed"), 1);
	convert_colors_to_int(&game, &data);
	if (!data.map)
		return (printf("Error:\nMap not loaded correctly\n"), 1);
	if (init_mlx(&game) != 0)
		return (1);
	if (!load_wall_textures(&game, &data))
		return (printf("Error:\nFailed to load textures\n"), 1);
	data.game = &game;
	render_frame(&data);
	setup_hooks(game, data);
	return (0);
}
