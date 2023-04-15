/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2023/04/15 17:04:48 by cmarcu           ###   ########.fr       */
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

double random_double()
{
	return (rand() / RAND_MAX + 1.0);
}

void shoot_ray(t_data *data, t_ray *ray, t_vec3 *aux)
{
	// t_vec3 origin = data->world->camera.from;
    // t_vec3 horizontal = vctor(data->view.width, 0, 0);
    // t_vec3 vertical = vctor(0, data->view.height, 0);
    // t_vec3 lower_left_corner = vec3_subs(vec3_subs(origin, vec3_division(horizontal, 2)), vec3_subs(vec3_division(vertical, 2), vctor(0, 0, data->world->camera.HFOV)));
	// // (origin - h/2) - (v/2 - HFOV)
	double u = ((double)aux->x) / (data->view.width-1); //Antialiasing ((double)aux->x + random_double())
	double v = ((double)aux->y) / (data->view.height-1);//Antialiasing ((double)aux->y + random_double())
	t_vec3 temp;
	ray->origin = data->world->camera.from;
	//ray->direction = vec3_add(vec3_add(data->world->camera.lower_left_corner, vec3_mult(data->world->camera.horizontal, u)), vec3_subs(vec3_mult(data->world->camera.vertical, v), data->world->camera.from));
	/*Todo esto debería ser lo mismo que ray(origin, lower_left_corner + s*horizontal + t*vertical - origin)*/
	ray->direction = vec3_mult(data->world->camera.horizontal, u);
	ray->direction = vec3_add(data->world->camera.lower_left_corner, ray->direction);
	temp = vec3_mult(data->world->camera.vertical, v);
	ray->direction = vec3_add(ray->direction, temp);
	ray->direction = vec3_subs(ray->direction, data->world->camera.from);
	ray->direction = vec3_normalize(ray->direction);
	
}

void render(t_data *data)
{
	t_vec3	aux;
	t_ray	ray;
	t_vec3	pixel_color;

	aux.y = 0;
	while (aux.y < data->view.height)
	{
		aux.x = 0;
        while (aux.x < data->view.width)
		{
			pixel_color = vctor(0, 0, 0);
			shoot_ray(data, &ray, &aux);
			pixel_color = vec3_add(ray_color(&ray, data->world), pixel_color);
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

double	degree_to_radian(double degree)
{
	return (degree * M_PI / 180);
}

t_camera init_camera(t_data *data)
{
	t_camera camera;
	
	/*TODO que venga del parser todo lo hardcodeado*/
	camera.from = vctor(-2, -2, -1);
	camera.HFOV = 120.0;
	camera.lookAt = vctor(0, 0, 1);
	/*_____________________________________________*/
	
	double theta;
	double field_width;

	theta = degree_to_radian(camera.HFOV);
	field_width = 2.0 * (double)tan(theta / 2);
	camera.viewport_width = field_width;
	camera.viewport_height = data->view.aspect_ratio * field_width;

	camera.w = vec3_normalize(vec3_subs(camera.from, camera.lookAt));
	camera.u = vec3_normalize(vec3_cross(vctor(0, 1, 0), camera.w));
	camera.v = vec3_cross(camera.w, camera.u);

	camera.horizontal = vec3_mult(camera.u, camera.viewport_width);
	camera.vertical = vec3_mult(camera.v, camera.viewport_height);
	camera.lower_left_corner = vec3_subs(vec3_subs(vec3_subs(camera.from, vec3_division(camera.horizontal, 2)), vec3_division(camera.vertical, 2)), camera.w);

	return (camera);
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

	data->world->lights = malloc(sizeof(t_object_list));
	data->world->lights->type = 3;
	data->world->lights->obj = NULL;
	data->world->lights->next = NULL;
	
	data->world->rec = (t_hit_record*)malloc(sizeof(t_hit_record));
	data->world->camera = init_camera(data);
	t_sphere *sphere1 = new_sphere(vctor(0, 0, 1), 0.5, vctor(0.5, 1, 1)); //azul
	t_sphere *sphere2 = new_sphere(vctor(0, 100.5, 1), 100, vctor(1, 1, 0.15)); //verde
	t_sphere *sphere3 = new_sphere(vctor(1, 0, 1), 1, vctor(1, 0.75, 1)); //rosa
	t_sphere *sphere4 = new_sphere(vctor(-1, 0, 1), 0.5, vctor(1, 1, 1)); //negra-gris
	add_obj_to_scene(data->world, (void*)sphere4);
	add_obj_to_scene(data->world, (void*)sphere2);
	add_obj_to_scene(data->world, (void*)sphere1);
	add_obj_to_scene(data->world, (void*)sphere3);
	/*______________________________________________________*/
	render(data);
	
	mlx_put_image_to_window(data->mlx,data->win, data->img, 0, 0);
	mlx_key_hook(data->win, hook_keydown, &data->mlx);
	mlx_hook(data->win, 17, 0, close_win, data);
	mlx_loop(data->mlx);
}
