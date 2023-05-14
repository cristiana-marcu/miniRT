/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bright.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/14 19:23:19 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "parser.h"

double	get_bright(char *str)
{
	double	bright;

	if (ft_strlen(str) != 3 || (str[0] != '0' && str[0] != '1'))
		return (-1);
	else if (str[1] != '.' || str[3] != '\0')
		return (-1);
	else if (str[2] < '0' || str[2] > '9')
		return (-1);
	else
	 	bright = ft_atof(str);
	if (bright > 1 || bright < 0)
		return (-1);
	else if (bright == 0 && (str[0] != '0' || str[2] != '0'))
		return (-1);
	return (bright);
}

