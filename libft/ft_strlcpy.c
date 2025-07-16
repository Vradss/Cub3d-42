/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:47:54 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/06 18:44:22 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* strlcpy() take the full size of the destination buffer and guarantee 
NUL-termination if there is room. room for NUL should be included in dstsize.
strlcpy() copies up to dstsize - 1 characters from the string src to dst,
NUL-terminating the result if dstsize is not 0.
Function returns the total length of the string it tried to create.
For strlcpy() that means the length of src. */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > i)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

/*int	main(void)
{
	char	dst[] = "testtesttesttesttest";
	char	src[] = "bubul";

	printf("%zu", ft_strlcpy(dst, src, 15));
}*/
