/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:02:39 by cmarcu            #+#    #+#             */
/*   Updated: 2021/01/27 14:00:13 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			a;

	p = (unsigned char *)b;
	a = 0;
	while (a < len)
	{
		p[a] = (unsigned char)c;
		a++;
	}
	return (b);
}
