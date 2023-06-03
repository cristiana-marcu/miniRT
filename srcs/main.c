/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2023/06/03 13:08:52 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
/*
void ch_leaks(void)
{
	system("leaks miniRT");
}
	atexit(ch_leaks);
*/

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){};
	if (check_scene(argc, argv))
		data.world = load_scene(argv[1]);
	else
		return (1);
	init_mlx(&data);
	data.world->camera = init_camera(&data);
	if (data.world->camera.hfov > 0)
		render(&data);
	start_rt(&data);
}
