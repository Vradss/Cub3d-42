/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:54:27 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/11 16:59:34 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* dest CAN overlap source.
copie src sur dst con memcpy, si src est inférieur à dst, il laisse en 
place les caractères de dst supérieurs à len */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	if (src == NULL && dst == NULL)
		return (NULL);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len--)
		{
			str1[len] = str2[len];
		}
	}
	return (dst);
}

/*int	main(void)
{
	char	src[] = "123456789";
	char	dst[] = "abcdefghijklmnop";

	printf("%s", ft_memmove(dst, src, 5));
}*/
