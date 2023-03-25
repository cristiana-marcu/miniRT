/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2023/03/25 16:57:16 by cmarcu           ###   ########.fr       */
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
    t_vec3 lower_left_corner = vec3_subs(vec3_subs(origin, vec3_division(horizontal, 2)), vec3_subs(vec3_division(vertical, 2), vctor(0, 0, data->world->camera.HFOV)));
	
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
            pixel_color = ray_color(&ray, data->world);
			my_mlx_pixel_put(data, aux.x, aux.y, vec3_toRGB(pixel_color));
			aux.x++;
        }
		aux.y++;
    }
}

t_object_list	*obj_lstnew(void *obj, int type)
{
	t_object_list	*result;

	result = ft_calloc(1, sizeof(t_object_list));
	if (!result)
		return (NULL);
	result->type = type;
	result->obj = obj;
	result->next = NULL;
	return (result);
}

void	obj_lstadd_back(t_object_list **lst, t_object_list *new)
{
	t_object_list	*last;

	if (!(*lst)->obj) //En la primera vuelta tendria que entrar por aqui
	{
		*lst = new;
		new->next = NULL;
		return ;
	}	
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
	return ;
}

void	*add_obj_to_scene(t_world *world, void *obj)
{
	t_object_list	*elem;

	elem = obj_lstnew(obj, 0); //TODO Parser: el type de objeto tiene que llegar de la escena
	if (!elem)
		return (NULL);
	obj_lstadd_back(&(world->objs), elem);
	return (obj);
}

t_sphere *new_sphere(t_vec3 center, double r, t_vec3 color)
{
	t_sphere *sph;

	sph = malloc(sizeof(t_sphere));
	if (!sph)
		return (NULL);
	sph->center = center;
	sph->r = r;
	sph->color  = color;
	return (sph);
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
	data->world->camera.from = vctor(0, 0, 0);
	data->world->camera.HFOV = 100.0;
	t_sphere *sphere1 = new_sphere(vctor(0, 0, 1), 0.5, vctor(0.5, 1, 1));
	t_sphere *sphere2 = new_sphere(vctor(0, 100.5, 1), 100, vctor(1, 1, 1));
	t_sphere *sphere3 = new_sphere(vctor(1, 0, 1), 0.5, vctor(1, 1, 1));
	t_sphere *sphere4 = new_sphere(vctor(1, 0, 1), -0.45, vctor(1, 1, 1));
	t_sphere *sphere5 = new_sphere(vctor(-1, 0, 1), 0.5, vctor(1, 1, 1));
	add_obj_to_scene(data->world, (void*)sphere1);
	add_obj_to_scene(data->world, (void*)sphere2);
	add_obj_to_scene(data->world, (void*)sphere3);
	add_obj_to_scene(data->world, (void*)sphere4);
	add_obj_to_scene(data->world, (void*)sphere5);
	/*______________________________________________________*/
	render(data);
	
	mlx_put_image_to_window(data->mlx,data->win, data->img, 0, 0);
	mlx_key_hook(data->win, hook_keydown, &data->mlx);
	mlx_hook(data->win, 17, 0, close_win, data);
	mlx_loop(data->mlx);
}
