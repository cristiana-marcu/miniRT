/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/09 20:27:16 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include "canvas.h"
#include "objects.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*a;
	size_t	i;

	a = (char *)malloc(count * size);
	if (!a)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		a[i] = 0;
		i++;
	}
	return ((void *)a);
}

int	hook_keydown(int key, t_data *mlx)
{
	if (key == K_ESC)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	close_win(t_data *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	exit(0);
}

t_data *init_mlx() //TODO pasar argv para chequear formatos
{
	t_data	*data;
	//TODO recoger los valores de resolución de los argv, aquí se duplican con el main

	data = (t_data *)malloc(sizeof(t_data)); //TODO proteger
	if (data == NULL)
		return (NULL);
	data->view.aspect_ratio = 16.0 / 9.0;
	data->view.width = 1080;
	data->view.height = (int)(data->view.width / data->view.aspect_ratio);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->view.width, data->view.height, "miniRT");
	data->img = mlx_new_image(data->mlx, data->view.width, data->view.height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
									&data->endian);
	return (data);
}

int	main(void)
{
	t_data	*data;

	data = init_mlx();

	/*TODO PARSER: Hardcodeado porque esto vendrá del parser*/
	data->world = malloc(sizeof(t_world));

	data->world->objs = malloc(sizeof(t_object_list));
	data->world->objs->type = 0;
	data->world->objs->obj = NULL;
	data->world->objs->next = NULL;

	data->world->rec = (t_hit_record*)malloc(sizeof(t_hit_record));
	data->world->camera = init_camera(data);
	data->world->amb_light = new_ambient_light(0.2, vctor(1, 1, 1));
	data->world->light = new_light(vctor(0, 2, 0), 0.5, vctor(1, 1, 1)); //luz blanca 255, 255, 255, revisar intensidad de 2
	t_sphere *sphere1 = new_sphere(vctor(-1.6, 0.5, -3.5), 1, vctor(0.5, 1, 1)); //azul
	t_sphere *sphere2 = new_sphere(vctor(-0.8, 0.5, -3), 1, vctor(1, 1, 0.15)); //verde
	t_sphere *sphere3 = new_sphere(vctor(0, 0.5, -2.5), 1, vctor(1, 0.75, 1)); //rosa
	t_sphere *sphere4 = new_sphere(vctor(0.8, 0.5, -3), 1, vctor(1, 1, 1)); //negra-gris
	t_sphere *sphere5 = new_sphere(vctor(1.6, 0.5, -3.5), 1, vctor(1, 0, 0)); //roja
	add_obj_to_scene(data->world, (void*)sphere1, 0);
	add_obj_to_scene(data->world, (void*)sphere2, 0);
	add_obj_to_scene(data->world, (void*)sphere3, 0);
	add_obj_to_scene(data->world, (void*)sphere4, 0);
	add_obj_to_scene(data->world, (void*)sphere5, 0);


	// t_cylinder *cyl1 = new_cylinder(vctor(-0.5, 0, 1), vctor(1, 0, 0), 0.5, 3, vctor(1, 0.1, 1));
	// add_obj_to_scene(data->world, (void*)cyl1, 2);

	t_plane *pl = new_plane(vctor(0, -1, 0), vctor(0, 1, 0), vctor(0, 0.51, 0.41));
	add_obj_to_scene(data->world, (void*)pl, 1);

	// t_plane *pl2 = new_plane(vctor(1, 0, 1), vctor(1, 0, 0), vctor(0, 1, 0.41));
	// add_obj_to_scene(data->world, (void*)pl2, 1);

	// t_plane *pl3 = new_plane(vctor(1, 0, 1), vctor(0, 0, 1), vctor(1, 0.51, 1));
	// add_obj_to_scene(data->world, (void*)pl3, 1);
	/*______________________________________________________*/
	render(data);

	mlx_put_image_to_window(data->mlx,data->win, data->img, 0, 0);
	mlx_key_hook(data->win, hook_keydown, &data->mlx);
	mlx_hook(data->win, 17, 0, close_win, data);
	mlx_loop(data->mlx);
}
