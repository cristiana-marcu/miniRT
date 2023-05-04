/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:12:04 by drontome          #+#    #+#             */
/*   Updated: 2022/12/07 18:48:57 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(char const *s, ...)
{
	va_list	ap;
	int		char_printed;

	va_start(ap, s);
	char_printed = 0;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			char_printed += ft_getformat(*s, ap);
		}
		else
			char_printed += ft_putchar(*s);
		s++;
	}
	va_end(ap);
	return (char_printed);
}
