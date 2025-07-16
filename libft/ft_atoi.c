/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:17:27 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/09/22 16:14:10 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* se añaden los 2 if del while para que el atoi funcione 
con over long max value*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				neg;
	unsigned long	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - 48) + (res * 10);
		if (res > 9223372036854775808UL && neg == -1)
			return (0);
		if (res > 9223372036854775808UL && neg == 1)
			return (-1);
		i++;
	}
	return (res * neg);
}

/*int	main(void)
{
	char	str[] = "  698585";

	printf("%d", ft_atoi(str));
}*/
