/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/15 16:30:42 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){};
	if (check_scene(argc, argv))
		data.world = load_scene(argv[1]);
	else
	{
		printf("NO HECHO\n");
		return (1);
	}
	init_mlx(&data);
	data.world->camera = init_camera(&data);
	render(&data);
	start_rt(&data);
}

