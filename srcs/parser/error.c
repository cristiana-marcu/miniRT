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
	if (err & E_BAD_ARG)
		ft_putstr_fd("\t- Just one argument valid\n", STDERR_FILENO);
	else if (err & E_EXTEN)
		ft_putstr_fd("\t- File does not end with '.rt'\n", STDERR_FILENO);
	else if (err & E_OPEN)
		ft_putstr_fd("\t- Could not open the file\n", STDERR_FILENO);
	if (err & E_EXIT)
	{
		ft_putstr_fd("Exit\n", STDERR_FILENO);
		exit(err ^ E_EXIT);
	}
}
