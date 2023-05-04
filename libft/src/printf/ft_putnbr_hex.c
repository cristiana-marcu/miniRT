/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 00:08:06 by drontome          #+#    #+#             */
/*   Updated: 2022/12/07 18:48:57 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length_hex(unsigned int nbr)
{
	int	c;

	c = 1;
	while (nbr >= 16)
	{
		nbr /= 16;
		c++;
	}
	return (c);
}

static void	ft_recursive_hex(unsigned int nbr, char c)
{
	if (nbr >= 16)
	{
		ft_recursive_hex(nbr / 16, c);
		ft_recursive_hex(nbr % 16, c);
	}
	else if (nbr <= 9)
		ft_putchar(nbr + '0');
	else if (c == 'x')
		ft_putchar(nbr - 10 + 'a');
	else if (c == 'X')
		ft_putchar(nbr - 10 + 'A');
}

int	ft_putnbr_hex(unsigned int nbr, char c)
{
	ft_recursive_hex(nbr, c);
	return (ft_length_hex(nbr));
}
