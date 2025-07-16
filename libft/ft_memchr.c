/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:36:57 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/09/22 16:10:46 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((unsigned char)c != ((unsigned char *)s)[i]))
		i++;
	if (i == n)
		return (NULL);
	return ((void *)s + i);
}

/*int	main(void)
{
	char	s[] = "blablabliblu";
	int	c;

	c = 'a';
	printf("%s", ft_memchr(s, c, 5));
	return (0);
}*/
