/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:14:31 by drontome          #+#    #+#             */
/*   Updated: 2022/06/29 15:52:20 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	ft_count_pointers(const char *s, char c)
{
	size_t		i;
	const char	*aux;

	aux = s;
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s && (s == aux || (*s != c && *(s - 1) == c)))
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static size_t	ft_count_string(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

static char	**ft_free_null(char **pp, size_t i)
{
	while (i--)
		free(pp[i]);
	free(pp);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**pp;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_count_pointers(s, c);
	pp = ft_calloc(len + 1, sizeof(s));
	if (!pp)
		return (NULL);
	i = 0;
	while (*s && i < len)
	{
		while (*s && *s == c)
			s++;
		pp[i] = ft_substr(s, 0, ft_count_string(s, c));
		if (!pp[i])
			return (ft_free_null(pp, i));
		while (*s && *s != c)
			s++;
		i++;
	}
	return (pp);
}
