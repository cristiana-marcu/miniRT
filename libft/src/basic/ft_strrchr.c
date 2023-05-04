/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:30:14 by drontome          #+#    #+#             */
/*   Updated: 2022/06/19 17:08:08 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*p;
	unsigned int	len;

	len = ft_strlen(s);
	p = (char *)(s + len);
	while (len-- > 0 && *p != (char)c)
		p--;
	if (*p == (char)c)
		return (p);
	else
		return (0);
}
