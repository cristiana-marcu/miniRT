/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:15:05 by cristianama       #+#    #+#             */
/*   Updated: 2023/05/26 18:50:00 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "ray.h"
#include <stdbool.h>
#include <stdio.h>

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
