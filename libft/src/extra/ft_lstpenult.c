/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpenult.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:42:54 by drontome          #+#    #+#             */
/*   Updated: 2023/01/07 11:38:15 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpenult(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL && lst->next->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
