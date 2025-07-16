/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:00:43 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/10 14:34:39 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*lst: Le début de la liste.
Valeur de retour : Dernier élément de la liste
Renvoie le dernier élément de la liste.*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	last = lst;
	while (last)
	{
		if (!(last->next))
			return (last);
		last = last->next;
	}
	return (last);
}

/*int main(int argc, const char *argv[])
{
	int			i;
	char		*content;
	t_list		*val;
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	char		*str = strdup("lorem");
	char		*str2 = strdup("ipsum");
	char		*str3 = strdup("dolor");

	elem = ft_lstnew(str);
	elem2 = ft_lstnew(str2);
	elem3 = ft_lstnew(str3);

	if (argc == 1 || !elem || !elem2 || !elem3)
		return (0);
	else if (atoi(argv[1]) == 1)
	{
		elem->next = elem2;
		elem2->next = elem3;
		val = ft_lstlast(elem);
		i = 0;
		content = val->content;
		while (content[i])
			write(1, &(content[i++]), 1);
		write(1, "\n", 1);
	}
	return (0);
}*/
