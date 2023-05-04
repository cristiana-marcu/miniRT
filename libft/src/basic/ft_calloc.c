/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:54:56 by drontome          #+#    #+#             */
/*   Updated: 2022/07/07 16:37:59 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	m;

	m = nmemb * size;
	if (m < nmemb && m < size)
		return (NULL);
	p = malloc(m);
	if (p == 0)
		return (0);
	ft_bzero(p, m);
	return (p);
}
