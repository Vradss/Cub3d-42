/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:48:19 by amdemuyn          #+#    #+#             */
/*   Updated: 2022/10/10 19:55:38 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Itère sur la liste ’lst’ et applique la fonction ’f’ au contenu de 
chaque élément.*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f (lst->content);
		lst = lst->next;
	}
}
