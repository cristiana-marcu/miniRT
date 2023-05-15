/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:15:05 by cristianama       #+#    #+#             */
/*   Updated: 2023/05/15 15:18:57 by cmarcu           ###   ########.fr       */
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

t_vec3	ray_at(t_ray *r, double point_on_ray)
{
	t_vec3	ray_at;

	ray_at = vec3_add(r->origin, vec3_mult(r->direction, point_on_ray));
	return (ray_at);
}

bool	hit_object(t_object_list *obj, t_ray *r, t_hit_record *rec)
{
	if (obj->type == SPHERE && hit_sphere(obj, r, rec))
		return (true);
	else if (obj->type == CYLINDER && hit_cylinder(obj, r, rec))
		return (true);
	else if (obj->type == PLANE && hit_plane(obj, r, rec))
		return (true);
	return (false);
}

t_vec3	calculate_pixel_color(t_world *world)
{
	t_ray			shadow_ray;
	t_object_list	*obj;
	t_hit_record	shadow_rec;

	shadow_ray = rctor(vec3_add(world->rec->hit_point, vec3_mult(world->rec->N, 0.001)), vec3_subs(world->light.pos, world->rec->hit_point));
	obj = world->objs;
	shadow_rec.t_min = EPSILON;
	shadow_rec.t_max = vec3_magn(vec3_subs(world->light.pos, world->rec->hit_point));
	while (obj)
	{
		if (hit_object(obj, &shadow_ray, &shadow_rec))
			return (ambient_light_on_obj(world));
		obj = obj->next;
	}
	return (clamp_color(vec3_add(ambient_light_on_obj(world), diffuse_light_on_obj(world, shadow_ray))));
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
		if (hit_object(obj, r, world->rec))
		{
			hit_anything = true;
			if (world->rec->t_max < closest_so_far)
				closest_so_far = world->rec->t;
			color = world->rec->color;
		}
		obj = obj->next;
	}
	if (hit_anything)
		return (calculate_pixel_color(world));
	return (vctor(0, 0, 0));
}

void	shoot_ray(t_data *data, t_ray *ray, t_vec3 *aux)
{
	double	u;
	double	v;

	u = ((double)aux->x) / (data->view.width - 1); //Antialiasing ((double)aux->x + random_double())
	v = 1 - ((double)aux->y) / (data->view.height - 1);//Antialiasing ((double)aux->y + random_double())
	ray->origin = data->world->camera.from;
	ray->direction = vec3_add(vec3_add(data->world->camera.lower_left_corner, vec3_mult(data->world->camera.horizontal, u)), vec3_subs(vec3_mult(data->world->camera.vertical, v), data->world->camera.from));
}
