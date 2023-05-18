/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:56:05 by drontome          #+#    #+#             */
/*   Updated: 2023/05/18 16:56:55 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_ob(t_object_list *lst, void (*del)(void*));

void	free_objs(t_object_list **lst, void (*del)(void*))
{
	t_object_list	*node;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		node = (*lst)->next;
		free_ob(*lst, del);
		*lst = node;
	}
	return ;
}

void	free_ob(t_object_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst->obj);
	free (lst);
	return ;
}
