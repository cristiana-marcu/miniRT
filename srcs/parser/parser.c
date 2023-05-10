/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/10 20:48:55 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minirt.h"

bool	check_scene(int argc, char **argv)
{
	int fd;

	fd = 0;
	if (argc != 2)
		print_err(E_BAD_ARG | E_EXIT);
	else if (ft_str_ends_with(argv[1], ".rt"))
		print_err(E_EXTEN | E_EXIT);
	else
		fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_err(E_OPEN | E_EXIT);
	return (false);
}

int main(int argc, char **argv)
{
	if (check_scene(argc, argv))
		printf("HECHO\n");
	else
		printf("NO HECHO\n");
}
