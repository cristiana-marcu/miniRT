/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_just_strchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:31:01 by drontome          #+#    #+#             */
/*   Updated: 2022/10/18 16:40:37 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_just_strchr(const char *chr, const char *str)
{
	while (chr && str && *str)
	{
		if (ft_strchr(chr, *str))
			str++;
		else
			return (0);
	}
	return (1);
}
