/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:40:43 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/18 18:06:45 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	if (!s)
		return (0);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen(s))
	{
			str[i] = s[start];
			start++;
			i++;
	}
	str[i] = 0;
	return (str);
}

/*int	main(void)
{
	char	s[] = "Magnifaique";
	
	printf("%s", ft_substr(s, 2, 4));
	return (0);
}*/
