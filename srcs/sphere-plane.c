/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere-plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:40:48 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/08 19:55:39 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "canvas.h"

t_sphere	*new_sphere(t_vec3 center, double r, t_vec3 color)
{
	t_sphere	*sph;

	sph = malloc(sizeof(t_sphere));
	if (!sph)
		return (NULL);
	sph->center = center;
	sph->r = r;
	sph->color = color;
	return (sph);
}

bool	hit_sphere(t_object_list *obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj->obj;

	t_vec3 oc = vec3_subs(ray->origin, sphere->center);
	double a = vec3_dot(ray->direction, ray->direction);
	double half_b = vec3_dot(oc, ray->direction);
	double c = vec3_dot(oc, oc) - sphere->r * sphere->r;
	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0.0)
		return (false);
	double root = (-half_b - sqrt(discriminant)) / a;
	if (root < rec->t_min || root > rec->t_max)
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (root < rec->t_min || root > rec->t_max)
			return (false);
	}
	rec->t = root;
	rec->hit_point = ray_at(ray, rec->t);
	rec->N = vec3_div(vec3_subs(rec->hit_point, sphere->center), sphere->r);
	set_face_normal(ray, rec);
	rec->t_max = rec->t;
	rec->color = sphere->color;
	return (true);
}

t_plane	*new_plane(t_vec3 pos, t_vec3 N, t_vec3 color)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->pos = pos;
	pl->N = N;
	pl->color = color;
	return (pl);
}

/*Ray-plane intersection equation:
	t = dot(N, P - Q) / dot(N, B)
	where B is ray direction, A its origin*/
bool	hit_plane(t_object_list *obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*plane;
	double	denominator;
	double	t;

	plane = (t_plane *)obj->obj;
	denominator = vec3_dot(plane->N, ray->direction);
	if (fabs(denominator) < EPSILON)
		return (false);
	t = vec3_dot(vec3_subs(plane->pos, ray->origin), plane->N) / denominator;
	if (t < rec->t_min || t > rec->t_max)
		return (false);
	rec->t = t;
	rec->hit_point = ray_at(ray, t);
	rec->N = plane->N;
	set_face_normal(ray, rec);
	rec->t_max = t;
	rec->color = plane->color;
	return (true);
}
