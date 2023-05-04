/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:10:40 by drontome          #+#    #+#             */
/*   Updated: 2022/06/27 15:07:22 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_is_neg(int n, int *neg)
{
	size_t	num;

	if (n < 0)
	{
		*neg = 1;
		if (n == -2147483648)
			return (2147483648);
		else
			num = (size_t) - n;
	}
	else
	{
		*neg = 0;
		num = (size_t)n;
	}
	return (num);
}

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

static char	*ft_putneg(char *p, int neg)
{
	if (neg == 1)
		*p = '-';
	return (p);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		neg;
	size_t	len;
	size_t	num;

	num = ft_is_neg(n, &neg);
	len = ft_len_num(num) + neg;
	p = ft_calloc(len + 1, sizeof(char));
	if (!p)
		return (NULL);
	p = ft_putnmbrs(p, num, len);
	return (ft_putneg(p, neg));
}
