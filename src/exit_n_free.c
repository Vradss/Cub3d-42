/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_n_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:17:22 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/24 19:54:17 by amdemuyn         ###   ########.fr       */
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
