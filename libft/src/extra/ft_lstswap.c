/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 10:16:43 by drontome          #+#    #+#             */
/*   Updated: 2023/01/02 11:33:43 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap(t_list *a, t_list *b)
{
	t_list	aux_a;
	t_list	aux_b;

	if (a && b)
	{
		aux_a = *a;
		aux_b = *b;
		*a = *b;
		a->next = aux_a.next;
		*b = aux_a;
		b->next = aux_b.next;
	}
	return ;
}
