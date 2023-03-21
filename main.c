/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2023/03/21 18:59:49 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"
#include <stdio.h>
#include <mlx.h>
#include "objects.h"

int	hook_keydown(int key, t_data *mlx)
{
	if (key == K_ESC)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	close()
{
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
	data->view.width = 720;
	data->view.height = (int)(data->view.width / data->view.aspect_ratio);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->view.width, data->view.height, "miniRT");
	data->img = mlx_new_image(data->mlx, data->view.width, data->view.height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
									&data->endian);
	return (data);
}

void shoot_ray(t_data *data, t_ray *ray, t_vec3 *aux)
{
	t_vec3 origin = vctor(0, 0, 0);
    t_vec3 horizontal = vctor(data->view.width, 0, 0);
    t_vec3 vertical = vctor(0, data->view.height, 0);
    t_vec3 lower_left_corner = vec3_subs(vec3_subs(origin, vec3_division(horizontal, 2)), vec3_subs(vec3_division(vertical, 2), vctor(0, 0, data->world.camera.HFOV)));
	
	double u = (double)aux->x / (data->view.width-1);
	double v = (double)aux->y / (data->view.height-1);
	ray->origin = vctor(0, 0, 0);
	ray->direction = vec3_add(vec3_add(lower_left_corner, vec3_mult(horizontal, u)), vec3_subs(vec3_mult(vertical, v), origin));
}

void render(t_data *data)
{
	t_vec3	aux;
	t_ray	ray;
	t_vec3	pixel_color;

	pixel_color = vctor(0, 0, 0);
	aux.y = 0;
	while (aux.y < data->view.height)
	{
		aux.x = 0;
        while (aux.x < data->view.width)
		{
			shoot_ray(data, &ray, &aux);
            pixel_color = ray_color(&ray, &data->world);
			my_mlx_pixel_put(data, aux.x, aux.y, vec3_toRGB(pixel_color));
			aux.x++;
        }
		aux.y++;
    }
}

t_object	*add_obj_to_scene(t_world *world, t_object *obj)
{
	t_list	*elem;

	elem = ft_lstnew(obj);
	if (!elem)
		return (NULL);
	ft_lstadd_back(&world->objs, elem);
	return (obj);
}

void *new_sphere(t_vec3 center, double r, t_vec3 color)
{
	void *sph;

	sph = malloc(sizeof(t_sphere));
	if (!sph)
		return (NULL);
	(t_sphere*)sph;
	sph->type = SPHERE;
	sph->pos = center;
	sph->color  = color;
	sph->intersect = &hit_sphere;
	return (sph);
}

int	main(void)
{
	t_data	*data;

	data = init_mlx();

	/*TODO PARSER: Hardcodeado porque esto vendrá del parser*/
	data->world.camera.from = vctor(0, 0, 0);
	data->world.camera.HFOV = 150.0;
	t_object *sphere = new_sphere(vctor(0, 0, -1), 0.5, vctor(1, 1, 1));
	sphere = add_obj_to_scene(&data->world, sphere);
	/*______________________________________________________*/
	render(data);
	
	mlx_put_image_to_window(data->mlx,data->win, data->img, 0, 0);
	mlx_key_hook(data->win, hook_keydown, &data->mlx);
	mlx_hook(data->win, 17, 0, close, NULL);
	mlx_loop(data->mlx);
}
