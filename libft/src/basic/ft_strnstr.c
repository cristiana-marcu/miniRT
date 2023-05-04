/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:02:18 by drontome          #+#    #+#             */
/*   Updated: 2022/06/29 15:54:52 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pair(char *str, char *to_find, size_t len)
{
	unsigned int	i;

	if (len < ft_strlen(to_find))
		return (0);
	i = 0;
	while (*(str + i) == *(to_find + i) && *(str + i) != 0)
		i++;
	if (*(to_find + i) == 0)
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack != 0 && len > 0)
	{
		if (ft_pair((char *)haystack, (char *)needle, len))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}
