/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:37:20 by cmarcu            #+#    #+#             */
/*   Updated: 2021/03/22 14:08:32 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	a = 0;
	while (haystack[a] != '\0' && a < len)
	{
		b = 0;
		while (haystack[a + b] == needle[b] && needle[b] != 0 && b + a < len)
			b++;
		if (b == ft_strlen(needle))
			return ((char *)(haystack + a));
		a++;
	}
	return (NULL);
}
