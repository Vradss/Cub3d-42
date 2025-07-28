/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_n_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrads <vrads@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:17:22 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/28 11:17:59 by vrads            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_error(char *info)
{
	ft_putstr_fd(info, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	free_array(void **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = -1;
	while (arr[++i] != NULL)
		free(arr[i]);
	free(arr);
}

int	close_window_hook(t_data *data)
{
	cleanup_and_exit(data);
	return (0);
}

void	cleanup_and_exit(t_data *data)
{
	if (!data || !data->game)
		exit(0);
	if (data->game->textures.north)
		mlx_destroy_image(data->game->mlx, data->game->textures.north);
	if (data->game->textures.south)
		mlx_destroy_image(data->game->mlx, data->game->textures.south);
	if (data->game->textures.west)
		mlx_destroy_image(data->game->mlx, data->game->textures.west);
	if (data->game->textures.east)
		mlx_destroy_image(data->game->mlx, data->game->textures.east);
	if (data->game->img)
		mlx_destroy_image(data->game->mlx, data->game->img);
	if (data->game->win)
		mlx_destroy_window(data->game->mlx, data->game->win);
	if (data->raw_map)
		free_array((void **)data->raw_map);
	if (data->game->map)
		free(data->game->map);
	exit(0);
}
