/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:38:46 by drontome          #+#    #+#             */
/*   Updated: 2022/06/25 18:17:58 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	c;

	if (!lst)
		return (0);
	c = 1;
	while (lst->next != NULL)
	{
		c++;
		lst = lst->next;
	}
	return (c);
}
