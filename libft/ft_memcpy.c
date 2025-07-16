/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:52:25 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/06 18:21:19 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* dest cannot overlap source at all */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	i = 0;
	str1 = (char *)dst;
	str2 = (char *)src;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (dst);
}

/*int	main(void)
{
	char	dst[] = "unafrase";
	char	src[] = "shit";

	printf("%s", ft_memcpy(dst, src, 6));
}*/
