/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:05:38 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/17 16:12:06 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
	{
		del (lst->content);
		free (lst);
	}
}

/*void	ft_print_result(t_list *elem)
{
	write(1, elem->content, strlen(elem->content));
}

void	ft_del(void *content)
{
	free(content);
}

int main(int argc, const char *argv[])
{
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	char		*str = strdup("lorem");
	char		*str2 = strdup("ipsum");
	char		*str3 = strdup("dolor");
	char		*str4 = strdup("sit");

	elem = ft_lstnew(str);
	elem2 = ft_lstnew(str2);
	elem3 = ft_lstnew(str3);
	elem4 = ft_lstnew(str4);
	if (argc == 1 || !elem || !elem2 || !elem3 || !elem4)
		return (0);
	elem->next = elem2;
	elem2->next = elem3;
	elem3->next = elem4;
	if (atoi(argv[1]) == 1)
	{
		ft_lstdelone(elem3, &ft_del);
		if (elem)
			ft_print_result(elem);
		write(1, "\n", 1);
		if (elem2)
			ft_print_result(elem2);
		write(1, "\n", 1);
		if (elem3)
			ft_print_result(elem3);
		write(1, "\n", 1);
		if (elem4)
			ft_print_result(elem4);
	}
	return (0);
}*/
