/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:06:05 by cmarcu            #+#    #+#             */
/*   Updated: 2021/01/28 12:55:56 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dstchar;
	char	*srcchar;
	size_t	a;

	dstchar = (char *)dst;
	srcchar = (char *)src;
	if (dst > src)
	{
		a = len;
		while (a--)
			dstchar[a] = srcchar[a];
	}
	else
	{
		ft_memcpy(dstchar, srcchar, len);
	}
	return (dst);
}
