/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:54:37 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/17 16:13:25 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Supprime et libère la mémoire de l’élément passé en paramètre, et de tous 
les éléments qui suivent, à l’aide de ’del’ et de free */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*clear;

	if (lst)
	{
		while (*lst)
		{
			clear = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = clear;
		}
	}
}
