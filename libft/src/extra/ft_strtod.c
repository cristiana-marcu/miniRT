/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 18:33:49 by drontome          #+#    #+#             */
/*   Updated: 2023/05/17 10:41:33 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	get_decimal(long double result, const char *str, int *index);

double	ft_strtod(const char *str, char **endptr)
{
	long double	result;
	double		sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	result = get_decimal(result, str, &i);
	if (endptr != NULL)
		*endptr = (char *)&str[i];
	return ((double)result * sign);
}

static double	get_decimal(long double result, const char *str, int *index)
{
	int			i;
	long double	dec;

	i = *index;
	dec = 0.1;
	if (str[i] == '.')
	{
		i++;
		while (ft_isdigit(str[i]))
		{
			result = result + (str[i] - '0') * dec;
			dec *= 0.1;
			i++;
		}
	}
	if (result != 0 && (result > DBL_MAX || result < DBL_MIN))
	{
		*index = 0;
		return (0);
	}
	*index = i;
	return (result);
}
