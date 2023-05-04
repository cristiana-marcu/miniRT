/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_ends_with.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:45:09 by drontome          #+#    #+#             */
/*   Updated: 2022/10/18 17:04:45 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_ends_with(const char *str, const char *end)
{
	size_t	len;
	size_t	end_len;

	len = ft_strlen(str);
	end_len = ft_strlen(end);
	return (ft_strncmp((str + len - end_len), end, end_len));
}
