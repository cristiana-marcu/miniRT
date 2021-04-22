/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:39:24 by cmarcu            #+#    #+#             */
/*   Updated: 2021/03/22 14:10:48 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			a;

	a = 0;
	str = (unsigned char *)s;
	while (a < n)
	{
		if (str[a] == (unsigned char)c)
			return ((void *)(str + a));
		a++;
	}
	return (NULL);
}
