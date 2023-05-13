/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 18:33:49 by drontome          #+#    #+#             */
/*   Updated: 2023/05/12 12:28:35 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	num;
	double	res;

	num = (double)ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str == '.')
		str++;
	else
		return (0);
	res = (double)ft_atoi(str);
	while (*str >= '0' && *str <= '9')
	{
		res /= 10;
		str++;
	}
	if (num >= 0)
		return (num + res);
	else
		return (num - res);
}
