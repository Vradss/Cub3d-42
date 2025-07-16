/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:59:11 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/07 16:53:37 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*s1: La chaîne de caractères à trimmer.
set: Le set de référence de caractères à trimmer.
Valeur de retour: La chaîne de caractères trimmée.
NULL si l’allocation échoue.

Alloue (avec malloc(3)) et retourne une copie de
la chaîne ’s1’, sans les caractères spécifiés
dans ’set’ au début et à la fin de la chaîne de
caractères.*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (ft_strrchr(set, s1[end]) && end > start)
		end--;
	return (ft_substr(s1, start, (end - start + 1)));
}

/*int	main(void)
{
	printf("%s", ft_strtrim("abracadabra", "abra"));
	return (0);
}*/
