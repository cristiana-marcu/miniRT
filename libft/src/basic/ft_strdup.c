/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 18:49:15 by drontome          #+#    #+#             */
/*   Updated: 2022/06/19 20:48:55 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*p;
	unsigned int	i;

	p = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	i = 0;
	if (p == 0)
		return (0);
	while (*(s1 + i))
	{
		*(p + i) = *(s1 + i);
		i++;
	}
	return (p);
}
