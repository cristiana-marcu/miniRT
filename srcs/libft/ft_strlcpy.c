/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:04:15 by cmarcu            #+#    #+#             */
/*   Updated: 2021/03/22 14:09:50 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t
	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	a;

	a = 0;
	if (!dst || !src)
		return (0);
	if (dstsize > 0)
	{
		while (src[a] != '\0' && a < (dstsize - 1))
		{
			dst[a] = src[a];
			a++;
		}
		dst[a] = '\0';
	}
	while (src[a] != '\0')
		a++;
	return (a);
}
