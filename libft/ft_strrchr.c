/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:13:46 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/06 18:10:00 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* locates the last occurrence of c */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c > 256)
		c %= 256;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

/*int	main(void)
{
	char	s[] = "Comment ça va petit chat";
	int	c;

	c = 'e';
	printf("%s", ft_strrchr(s, c));
	return (0);
}*/
