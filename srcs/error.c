/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:11:09 by drontome          #+#    #+#             */
/*   Updated: 2023/05/08 18:21:29 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

void print_err(uint16_t err)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (err & E_BADARG)
		ft_putstr_fd("\t- Just one argument valid\n", 2);
	else if (err & E_EXT)
		ft_putstr_fd("\t- File does not end with '.rt'\n", STDERR_FILENO);

}
