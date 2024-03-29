/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:11:09 by drontome          #+#    #+#             */
/*   Updated: 2023/05/29 20:22:02 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_err2(uint32_t err);

void	print_err(uint32_t err)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (err & E_BAD_ARG)
		ft_putstr_fd("\t- Just one argument valid\n", STDERR_FILENO);
	if (err & E_EXTEN)
		ft_putstr_fd("\t- File does not end with '.rt'\n", STDERR_FILENO);
	if (err & E_OPEN)
		ft_putstr_fd("\t- Could not open the file\n", STDERR_FILENO);
	if (err & E_CHAR)
		ft_putstr_fd("\t- Invalid character inside scene\n", STDERR_FILENO);
	if (err & E_EMPTY)
		ft_putstr_fd("\t- The scene is empty\n", STDERR_FILENO);
	if (err & E_MEM)
		ft_putstr_fd("\t- Memory allocation failure\n", STDERR_FILENO);
	if (err & E_ID)
		ft_putstr_fd("\t- Wrong identifier detected\n", STDERR_FILENO);
	if (err & E_DUP_AMB)
		ft_putstr_fd("\t- Ambient light must be declared just once\n",
			STDERR_FILENO);
	if (err & E_DUP_CAM)
		ft_putstr_fd("\t- Camera must be declared just once\n", STDERR_FILENO);
	print_err2(err);
}

static void	print_err2(uint32_t err)
{
	if (err & E_DUP_LIT)
		ft_putstr_fd("\t- Light must be declared just once\n", STDERR_FILENO);
	if (err & E_AMB)
		ft_putstr_fd("\t- Ambient: range incorrect\n", STDERR_FILENO);
	if (err & E_CAM)
		ft_putstr_fd("\t- Camera: range incorrect\n", STDERR_FILENO);
	if (err & E_LIT)
		ft_putstr_fd("\t- Light: range incorrect\n", STDERR_FILENO);
	if (err & E_SP)
		ft_putstr_fd("\t- Sphere: range incorrect\n", STDERR_FILENO);
	if (err & E_PL)
		ft_putstr_fd("\t- Plane: range incorrect\n", STDERR_FILENO);
	if (err & E_CY)
		ft_putstr_fd("\t- Cylinder: range incorrect\n", STDERR_FILENO);
	if (err & E_EXIT)
	{
		ft_putstr_fd("Exit\n", STDERR_FILENO);
		exit(err ^ E_EXIT);
	}
}
