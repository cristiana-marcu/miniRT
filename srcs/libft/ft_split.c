/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:43:13 by cmarcu            #+#    #+#             */
/*   Updated: 2021/03/22 15:22:25 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_mountarray(char const *s, char c)
{
	size_t	result;
	char	*aux;
	char	**array;

	result = 0;
	aux = (char *)s;
	while (*aux)
	{
		while (*aux == c)
			aux++;
		if (*aux != '\0')
			result++;
		while (*aux && *aux != c)
			aux++;
	}
	array = (char **)malloc((result + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	return (array);
}

static char	**ft_fill_array(char const *s, char **array, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			while (s[j] && s[j] != c)
				j++;
			array[i++] = ft_substr(s, 0, j);
			s = s + j;
		}
		j = 0;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = ft_mountarray(s, c);
	if (!array)
		return (NULL);
	return (ft_fill_array(s, array, c));
}
