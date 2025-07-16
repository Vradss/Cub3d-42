/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:24:11 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/03 19:10:13 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*void	test(unsigned int i, char *c)
{
	static int indexArray[11] = {0};
		indexArray[i] = 1;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
	else if (*c >= 'A' && *c <= 'Z')
		*c += 32;
}

int		main(void)
{
	char	*str;

	str = (char *)malloc(sizeof(*str) * 12);

		strcpy(str, "LoReMiPsUm");
		ft_striteri(str, &test);
		write(1, str, 11);
	
	return (0);
}*/
