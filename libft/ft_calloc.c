/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vflorez <vflorez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:34:00 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/17 16:51:32 by vflorez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

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
