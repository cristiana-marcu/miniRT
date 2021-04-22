/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:13:56 by cmarcu            #+#    #+#             */
/*   Updated: 2021/03/22 14:10:24 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*copy;
	unsigned int	a;

	copy = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
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
