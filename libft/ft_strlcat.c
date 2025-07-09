/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:21:16 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/18 17:52:59 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* strlcat() appends string src to the end of dst.  It will append at most
dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless
dstsize is 0 or the original dst string was longer than dstsize 
Function returns the total length of the string it tried to create.
For strlcat() that means the initial length of dst plus the length of src. */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dstsize == 0 && (!dst || !src))
		return (0);
	while (dst[i] && i < dstsize)
		i++;
	while (src[j] && (i + j + 1) < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}

/*int	main(void)
{
	char	dst[] = "fuck";
	char	src[] = "tarace";
	printf("%zu", ft_strlcat(dst, src, 30));
}*/
