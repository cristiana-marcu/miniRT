/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:15:05 by cristianama       #+#    #+#             */
/*   Updated: 2023/04/29 18:41:32 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "canvas.h"


double random_double()
{
	return (rand() / RAND_MAX + 1.0);
}

t_ray rctor(t_vec3 origin, t_vec3 direction)
{
	t_ray r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_vec3 rayAt(t_ray *r, double pointOnRay)
{
    t_vec3 ray_at;
    
    ray_at = vec3_add(r->origin, vec3_mult(r->direction, pointOnRay));
    return (ray_at);
}

bool hit_object(t_object_list *obj, t_ray *r, t_hit_record *rec, t_vec3 *color)
{
    if (obj->type == SPHERE && hit_sphere(obj, r, rec))
    {
        *color = ((t_sphere*)(obj->obj))->color;
        return (true);
    }
    else if (obj->type == CYLINDER && hit_cylinder(obj, r, rec))
    {
        *color = ((t_cylinder*)(obj->obj))->color;
        return (true);
    }
    else if (obj->type == PLANE && hit_plane(obj, r, rec))
    {
        *color = ((t_plane*)(obj->obj))->color;
        return (true);
    }
    return (false);
}

t_vec3 ray_color(t_ray *r, t_world *world)
{
    bool hit_anything;
    double closest_so_far;
    t_object_list *obj;
    t_vec3 color;
    
    world->rec->t_min = EPSILON;
    world->rec->t_max = INFINITY;
    
    obj = world->objs;
    closest_so_far = world->rec->t_max;
	while (obj)
    {
        if (hit_object(obj, r, world->rec, &color))
        {
            hit_anything = true;
            if (world->rec->t_max < closest_so_far)
                closest_so_far = world->rec->t;
        }       
        obj = obj->next;
    }
    if (hit_anything)
        return (vec3_mult(color, vec3_dot(vec3_normalize(world->rec->N), vec3_normalize(vctor(-1, -1, -1)))));
    t_vec3 unit_direction = vec3_normalize(r->direction);
    hit_anything = 0.5*(unit_direction.y + 1.0);
    return vec3_add(vec3_mult(vctor(1.0, 1.0, 1.0), (1.0-hit_anything)), vec3_mult(vctor(0.5, 0.7, 1.0), hit_anything));
}

void shoot_ray(t_data *data, t_ray *ray, t_vec3 *aux)
{
	double u;
	double v;
	t_vec3 temp;

	u = ((double)aux->x) / (data->view.width-1); //Antialiasing ((double)aux->x + random_double())
	v = ((double)aux->y) / (data->view.height-1);//Antialiasing ((double)aux->y + random_double())
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