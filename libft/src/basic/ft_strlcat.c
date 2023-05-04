/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:54:53 by drontome          #+#    #+#             */
/*   Updated: 2022/06/18 17:31:45 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	cs;
	size_t	cd;
	size_t	res;

	cs = ft_strlen(src);
	cd = ft_strlen(dst);
	if (size < cd)
		return (cs + size);
	if (size == 0)
		return (cs);
	res = size - cd;
	dst = dst + cd;
	while (*(src) && res > 1)
	{
		*(dst) = *(src);
		src++;
		dst++;
		res--;
	}
	*dst = '\0';
	return (cd + cs);
}
