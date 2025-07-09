/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:34:00 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/19 13:59:25 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (!count || (count && SIZE_MAX / count > size))
	{
		ptr = malloc(count * size);
		if (ptr == NULL)
			return (ptr);
		ft_bzero(ptr, size * count);
	}
	return (ptr);
}
