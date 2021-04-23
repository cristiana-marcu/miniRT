/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:39:28 by cmarcu            #+#    #+#             */
/*   Updated: 2021/02/10 12:16:28 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t result;

	result = 0;
	while (*str != '\0')
	{
		result++;
		str++;
	}
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	a;
	size_t	length;

	length = ft_strlen(s);
	a = 0;
	while (a <= length)
	{
		if (s[a] == (char)c)
			return ((char*)(s + a));
		a++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (NULL);
	p = (char*)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	a = 0;
	while (s1[a] != '\0')
	{
		p[a] = s1[a];
		a++;
	}
	b = 0;
	while (s2[b] != '\0')
	{
		p[a] = s2[b];
		a++;
		b++;
	}
	p[a] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	a;

	if (!s)
		return (NULL);
	if (!(p = (char*)malloc(sizeof(*s) * (len + 1))))
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
		start = ft_strlen(s);
	a = 0;
	while (a < len && s[start])
	{
		p[a] = s[start + a];
		a++;
	}
	p[a] = '\0';
	return (p);
}

char	*ft_strdup(const char *s1)
{
	char			*copy;
	unsigned int	a;

	copy = (char*)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!copy)
		return (NULL);
	a = 0;
	while (s1[a] != '\0')
	{
		copy[a] = s1[a];
		a++;
	}
	copy[a] = '\0';
	return (copy);
}
