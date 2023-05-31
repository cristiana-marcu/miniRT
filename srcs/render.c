/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:42:19 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/26 18:50:04 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "canvas.h"

void	set_face_normal(t_ray *ray, t_hit_record *rec)
{
	rec->front_face = vec3_dot(ray->direction, rec->n) < 0;
	if (rec->front_face == false)
		rec->n = vec3_negate(rec->n);
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

void	obj_lstadd_back(t_object_list **lst, t_object_list *new_obj)
{
	t_object_list	*last;

	if (!(*lst)) //En la primera vuelta tendria que entrar por aqui
	{
		*lst = new_obj;
		new_obj->next = NULL;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new_obj;
	new_obj->next = NULL;
	return ;
}

void	*add_obj_to_scene(t_world *world, void *obj, int type)
{
	t_object_list	*elem;

	elem = obj_lstnew(obj, type); //TODO Parser: el type de objeto tiene que llegar de la escena
	if (!elem)
		return (NULL);
	obj_lstadd_back(&(world->objs), elem);
	return (obj);
}
/**
 * The function renders an image by shooting rays and calculating the color of
 * each pixel.
 *
 * @param data a pointer to a struct that contains information about the scene
 * and the image being rendered.
 */

void	render(t_data *data)
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
			shoot_ray(data, &ray, &aux);
			pixel_color = ray_color(&ray, data->world);
			my_mlx_pixel_put(data, aux.x, aux.y, vec3_to_rgb(pixel_color));
			aux.x++;
		}
		aux.y++;
	}
}
