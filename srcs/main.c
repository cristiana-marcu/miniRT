/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:24:01 by drontome          #+#    #+#             */
/*   Updated: 2023/05/08 18:32:06 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_scene(int argc, char **argv)
{
	if (argc != 2)
		print_err(E_BADARG);
	else if (!ft_str_ends_with(argv[1], ".rt"))
		print_err(E_EXT);
	else
		return (true);
	return (false);
}

int main(int argc, char **argv)
{
	if (check_scene(argc, argv))
		printf("HECHO\n");
}
