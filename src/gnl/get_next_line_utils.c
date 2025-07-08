/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vradis <vradis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:38:18 by vflorez           #+#    #+#             */
/*   Updated: 2024/08/17 13:52:54 by vradis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr_gnl(const char *str, int c)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == (char)c)
			return (1);
		str++;
	}
	return (0);
}

void	*ft_calloc_gnl(size_t num_elements, size_t size)
{
	char			*memory_allocated;
	unsigned int	i;

	memory_allocated = (char *)malloc(num_elements * size);
	if (memory_allocated == NULL)
		return (NULL);
	i = 0;
	while (i < (num_elements * size))
		memory_allocated[i++] = '\0';
	return ((void *)memory_allocated);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	int		i;

	if (!s1)
	{
		s1 = ft_calloc_gnl(1, sizeof(char));
		if (!s1)
			return (free(s1), s1 = NULL, NULL);
	}
	if (!s1 || !s2)
		return (free(s1), s1 = NULL, NULL);
	result = (char *)ft_calloc_gnl((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1),
			sizeof(char));
	if (!result)
		return (free(s1), s1 = NULL, NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	i = -1;
	while (s2[++i])
		result[ft_strlen_gnl(s1) + i] = s2[i];
	result[ft_strlen_gnl(s1) + i] = '\0';
	return (free(s1), s1 = NULL, result);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}
