/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:44:25 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/05 16:53:02 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*lst: Le début de la liste.
Valeur de retour : Taille de la liste
Compte le nombre d’éléments de la liste.*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/*int main(int argc, const char *argv[])
{
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	char		c;
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
		c = ft_lstsize(elem) + 48;
		write(1, &c, 1);
		write(1, "\n", 1);
	}
	return (0);
}*/
