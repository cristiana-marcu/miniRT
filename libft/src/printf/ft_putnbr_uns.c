/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:34:57 by drontome          #+#    #+#             */
/*   Updated: 2022/12/07 18:48:57 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_num(size_t n)
{
	size_t	len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_putnmbrs(char *p, size_t n, size_t len)
{
	while (n > 9 && len > 0)
	{
		*(p + len - 1) = n % 10 + 48;
		n /= 10;
		len--;
	}
	*(p + len - 1) = n + 48;
	return (p);
}

static char	*ft_itoa_uns(unsigned int n)
{
	char	*p;
	size_t	len;
	size_t	num;

	num = n;
	len = ft_len_num(num);
	p = ft_calloc(len + 1, sizeof(char));
	if (!p)
		return (NULL);
	p = ft_putnmbrs(p, num, len);
	return (p);
}

int	ft_putnbr_uns(unsigned int ap)
{
	int		c;
	char	*p;

	p = ft_itoa_uns(ap);
	c = ft_putstr(p);
	free(p);
	return (c);
}
