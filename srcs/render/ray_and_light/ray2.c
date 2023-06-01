/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:15:05 by cristianama       #+#    #+#             */
/*   Updated: 2023/06/01 18:52:46 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "ray.h"

t_vec3	calculate_pixel_color(t_world *world)
{
	t_ray			shadow_ray;
	t_object_list	*obj;
	t_hit_record	shadow_rec;

	shadow_ray = rctor(vec3_add(world->rec->hit_point, vec3_mult(world->rec->n,
					0.001)), vec3_norm(vec3_subs(world->light.pos,
					world->rec->hit_point)));
	obj = world->objs;
	shadow_rec.t_min = EPSILON;
	shadow_rec.t_max = vec3_magn(vec3_subs(world->light.pos,
				world->rec->hit_point));
	while (obj)
	{
		if (hit_object(obj, &shadow_ray, &shadow_rec))
			return (ambient_light_on_obj(world));
		obj = obj->next;
	}
	return (clamp_color(vec3_add(ambient_light_on_obj(world),
				diffuse_light_on_obj(world, shadow_ray))));
}

t_vec3	ray_color(t_ray *r, t_world *world)
{
	bool			hit_anything;
	double			closest_so_far;
	t_object_list	*obj;

	hit_anything = false;
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

	u = ((double)aux->x) / (data->view.width - 1);
	v = 1 - ((double)aux->y) / (data->view.height - 1);
	ray->origin = data->world->camera.from;
	ray->direction = vec3_norm(vec3_add(vec3_add(\
		data->world->camera.lower_left_corner, \
		vec3_mult(data->world->camera.horizontal, u)), \
		vec3_subs(vec3_mult(data->world->camera.vertical, v), \
		data->world->camera.from)));
}
