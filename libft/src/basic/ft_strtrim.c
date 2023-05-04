/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:49:18 by drontome          #+#    #+#             */
/*   Updated: 2022/06/22 18:34:55 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_start(char const *s1, char const *set)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)set;
	while (*p && *s1)
	{
		while (*s1 == *p)
		{
			s1++;
			i++;
			p = (char *)set;
		}
		p++;
	}
	return (i);
}

static size_t	ft_count_end(char const *s1, char const *set)
{
	size_t	l;
	char	*p;

	l = ft_strlen(s1) - 1;
	p = (char *)set;
	while (*p && l > 0)
	{
		while (*(s1 + l) == *p && l > 0)
		{
			l--;
			p = (char *)set;
		}
		p++;
	}
	return (l);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*p;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set || !*set)
		return (ft_strdup(s1));
	if (!*s1)
		return (ft_strdup(""));
	i = ft_count_start(s1, set);
	len = ft_count_end(s1, set);
	if (i > len)
		return (ft_strdup(""));
	p = ft_calloc(len - i + 2, sizeof(char));
	if (!p)
		return (NULL);
	ft_strlcpy(p, (s1 + i), (len - i + 2));
	return (p);
}
