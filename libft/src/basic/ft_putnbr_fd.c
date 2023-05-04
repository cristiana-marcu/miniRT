/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:56:25 by drontome          #+#    #+#             */
/*   Updated: 2022/06/29 15:51:51 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_is_neg(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == -2147483648)
			return (2147483648);
		else
			return ((size_t) - n);
	}
	else
		return ((size_t)n);
}

static void	ft_putnbr(size_t nbr, int fd)
{
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10, fd);
		nbr = nbr % 10;
	}
	if (nbr <= 9)
	{
		nbr += '0';
		write(fd, &nbr, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	num;

	num = ft_is_neg(n, fd);
	ft_putnbr(num, fd);
	return ;
}
