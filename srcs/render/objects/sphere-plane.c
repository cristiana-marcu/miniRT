/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere-plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:40:48 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/29 20:35:19 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "ray.h"

bool	hit_sphere(t_object_list *obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sphere;
	t_sp_cal	cal;

	sphere = (t_sphere *)obj->obj;
	cal.oc = vec3_subs(ray->origin, sphere->center);
	cal.a = vec3_dot(ray->direction, ray->direction);
	cal.half_b = vec3_dot(cal.oc, ray->direction);
	cal.c = vec3_dot(cal.oc, cal.oc) - sphere->r * sphere->r;
	cal.discr = cal.half_b * cal.half_b - cal.a * cal.c;
	if (cal.discr < 0.0)
		return (false);
	cal.root = (-cal.half_b - sqrt(cal.discr)) / cal.a;
	if (cal.root < rec->t_min || cal.root > rec->t_max)
	{
		cal.root = (-cal.half_b + sqrt(cal.discr)) / cal.a;
		if (cal.root < rec->t_min || cal.root > rec->t_max)
			return (false);
	}
	rec->t = cal.root;
	rec->hit_point = ray_at(ray, rec->t);
	rec->n = vec3_div(vec3_subs(rec->hit_point, sphere->center), sphere->r);
	set_face_normal(ray, rec);
	rec->t_max = rec->t;
	rec->color = sphere->color;
	return (true);
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
	denominator = vec3_dot(plane->n, ray->direction);
	if (fabs(denominator) < EPSILON)
		return (false);
	t = vec3_dot(vec3_subs(plane->pos, ray->origin), plane->n) / denominator;
	if (t < rec->t_min || t > rec->t_max)
		return (false);
	rec->t = t;
	rec->hit_point = ray_at(ray, t);
	rec->n = plane->n;
	set_face_normal(ray, rec);
	rec->t_max = t;
	rec->color = plane->color;
	return (true);
}
