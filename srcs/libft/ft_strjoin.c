/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:25:44 by cmarcu            #+#    #+#             */
/*   Updated: 2021/03/22 14:10:16 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (NULL);
	p = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	a = 0;
	while (s1[a] != '\0')
	{
		p[a] = s1[a];
		a++;
	}
	b = a;
	a = 0;
	while (s2[a] != '\0')
	{
		p[b] = s2[a];
		a++;
		b++;
	}
	p[b] = '\0';
	return (p);
}
