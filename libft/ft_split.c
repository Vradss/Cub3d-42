/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:53:20 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/18 18:20:01 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_split primera llama a count_words para reservar tantos punteros como
palabras. Despues va recorriendo el string hasta encontrar el 1er espacio,
llama a word_sep y reinicializa index a -1, si hay mas cadena que recorrer,
pasa el valor de i a index para seguir hasta el prox espacio o fin de cadena.
count_words: con i recorre el string hasta encontrarse con c(=espacio) y va 
aumentado word cada vez que se encuentra con un espacio.
word_sep: pinta la cadena propia de cada palabra */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			word++;
			while (str[i] != c && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				return (word);
		}
		i++;
	}
	return (word);
}

static char	*word_sep(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (end - start +1));
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	*ft_splat(size_t i, char const *s, char c, char **split)
{
	size_t	j;
	int		index;

	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_sep(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split[j]);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	ft_splat(i, s, c, split);
	return (split);
}

/*int	main(void)
{
	char	str[] = "hello how are you sweetie?";
	char	**word_split;
	char	c = ' ';
	word_split = ft_split(str, c);
	printf("%s\n", word_split[0]);
	printf("%s\n", word_split[1]);
	printf("%s\n", word_split[2]);
	printf("%s\n", word_split[3]);
	printf("%s\n", word_split[4]);
	return (0);
}*/
