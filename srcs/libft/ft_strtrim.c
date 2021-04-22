/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:05:31 by cmarcu            #+#    #+#             */
/*   Updated: 2021/03/22 14:07:27 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char_in_set(char c, char const *set)
{
	int	a;

	a = 0;
	while (set[a])
	{
		if (set[a] == c)
			return (1);
		a++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	int		a;
	int		start;
	int		end;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && is_char_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (start < end && is_char_in_set(s1[end], set))
		end--;
	p = (char *)malloc(sizeof(*s1) * (end - start + 2));
	if (!p)
		return (NULL);
	a = 0;
	while (a <= end - start)
	{
		p[a] = s1[start + a];
		a++;
	}
	p[a] = '\0';
	return (p);
}
