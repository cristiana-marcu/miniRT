/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:15:05 by cristianama       #+#    #+#             */
/*   Updated: 2023/05/07 14:16:39 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "canvas.h"

double	random_double(void)
{
	return (rand() / RAND_MAX + 1.0);
}

t_ray	rctor(t_vec3 origin, t_vec3 direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_vec3	ray_at(t_ray *r, double pointOnRay)
{
	t_vec3	ray_at;

	ray_at = vec3_add(r->origin, vec3_mult(r->direction, pointOnRay));
	return (ray_at);
}

bool	hit_object(t_object_list *obj, t_ray *r, t_hit_record *rec, t_vec3 *color)
{
	if (obj->type == SPHERE && hit_sphere(obj, r, rec))
	{
		*color = ((t_sphere *)(obj->obj))->color;
		return (true);
	}
	else if (obj->type == CYLINDER && hit_cylinder(obj, r, rec))
	{
		*color = ((t_cylinder *)(obj->obj))->color;
		return (true);
	}
	else if (obj->type == PLANE && hit_plane(obj, r, rec))
	{
		*color = ((t_plane *)(obj->obj))->color;
		return (true);
	}
	return (false);
}

t_vec3	illumination(t_world *world)
{
	t_vec3		color;
	t_ray			ray;
	t_object_list	*obj;
	double			intensity;

	ray = rctor(world->rec->hit_point, vec3_subs(world->light->pos, world->rec->hit_point));
	obj = world->objs;
	while (obj)
	{
		if (hit_object(obj, &ray, world->rec, &color))
			break;
		obj = obj->next;
	}
	//calcular color de objeto + luz;
	intensity = world->light->brightness * vec3_dot(vec3_norm(world->rec->N), vec3_norm(vec3_subs(world->light->pos, world->rec->hit_point)));
	return (vec3_mult(color, vec3_magn(vec3_mult(world->light->color, intensity * 0.2))));
}

t_vec3	ray_color(t_ray *r, t_world *world)
{
	bool			hit_anything;
	double			closest_so_far;
	t_object_list	*obj;
	t_vec3			color;

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
		return (illumination(world));
	return (vec3_add(vec3_mult(vctor(1.0, 1.0, 1.0), (1.0 - hit_anything)), vec3_mult(vctor(0.5, 0.7, 1.0), hit_anything)));
}

void	shoot_ray(t_data *data, t_ray *ray, t_vec3 *aux)
{
	double	u;
	double	v;

	u = ((double)aux->x) / (data->view.width - 1); //Antialiasing ((double)aux->x + random_double())
	v = ((double)aux->y) / (data->view.height - 1);//Antialiasing ((double)aux->y + random_double())
	ray->origin = data->world->camera.from;
	ray->direction = vec3_add(vec3_add(data->world->camera.lower_left_corner, vec3_mult(data->world->camera.horizontal, u)), vec3_subs(vec3_mult(data->world->camera.vertical, v), data->world->camera.from));
}
