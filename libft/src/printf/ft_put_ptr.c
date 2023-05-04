/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:09:00 by drontome          #+#    #+#             */
/*   Updated: 2022/12/07 18:48:57 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length_ptr(uintptr_t nbr)
{
	int	c;

	c = 0;
	while (nbr != 0)
	{
		nbr /= 16;
		c++;
	}
	return (c);
}

static void	ft_recursive_ptr(uintptr_t nbr)
{
	if (nbr >= 16)
	{
		ft_recursive_ptr(nbr / 16);
		ft_recursive_ptr(nbr % 16);
	}
	else if (nbr <= 9)
		ft_putchar(nbr + '0');
	else
		ft_putchar(nbr - 10 + 'a');
}

int	ft_put_ptr(void *ap)
{
	uintptr_t	p;
	int			c;

	p = (unsigned long)ap;
	c = 0;
	c += write(1, "0x", 2);
	if (p == 0)
		c += write(1, "0", 1);
	else
	{
		ft_recursive_ptr(p);
		c += ft_length_ptr(p);
	}
	return (c);
}
