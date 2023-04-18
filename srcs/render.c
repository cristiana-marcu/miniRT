/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:42:19 by cmarcu            #+#    #+#             */
/*   Updated: 2023/04/18 14:49:57 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "canvas.h"

void	set_face_normal(t_ray *ray, t_hit_record *rec)
{
	rec->front_face = vec3_dot(ray->direction, rec->N) < 0;
	if (rec->front_face == false)
		rec->N = vec3_negate(rec->N);
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