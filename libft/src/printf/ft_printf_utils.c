/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:37:26 by drontome          #+#    #+#             */
/*   Updated: 2022/12/07 18:48:57 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *ap)
{
	int	c;

	c = 0;
	if (ap == NULL)
	{
		return (ft_putstr("(null)"));
	}
	while (*(ap + c))
	{
		write(1, (ap + c), 1);
		c++;
	}
	return (c);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_getformat(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (c == 'p')
		return (ft_put_ptr(va_arg(ap, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_int(va_arg(ap, int)));
	else if (c == 'u')
		return (ft_putnbr_uns(va_arg(ap, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_putnbr_hex(va_arg(ap, unsigned int), c));
	else if (c == '%')
		return (ft_putchar(c));
	return (0);
}
