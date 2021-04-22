/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:23:33 by cmarcu            #+#    #+#             */
/*   Updated: 2021/01/29 13:16:55 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*copy;
	unsigned int	a;

	if (!s)
		return (NULL);
	copy = ft_strdup(s);
	if (!copy)
		return (NULL);
	a = 0;
	while (copy[a] != '\0')
	{
		copy[a] = (*f)(a, copy[a]);
		a++;
	}
	return (copy);
}
