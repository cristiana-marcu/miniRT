/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:46:43 by cmarcu            #+#    #+#             */
/*   Updated: 2021/04/02 16:32:02 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_length(long long int n)
{
	int	length;

	length = 0;
	if (n < 0)
		length++;
	if (n == 0)
		length = 1;
	while (n != 0)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

static void	ft_if_zero(long long int n, char *str)
{
	if (n == 0)
		str[0] = '0';
}

char	*ft_itoa(long long int n)
{
	char	*str;
	int		length;

	length = itoa_length(n);
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	str[length] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str[length-- - 1] = '8';
			n = n / 10;
		}
		n = -n;
	}
	ft_if_zero(n, str);
	while (length >= 0 && n != 0)
	{
		str[length-- - 1] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
