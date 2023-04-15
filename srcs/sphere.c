/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:40:48 by cmarcu            #+#    #+#             */
/*   Updated: 2023/04/15 17:44:52 by cmarcu           ###   ########.fr       */
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

bool hit_sphere(t_object_list *obj, t_ray *ray,t_hit_record *rec)
{
	t_sphere *sphere;

	sphere = (t_sphere*)obj->obj;
	
	t_vec3 oc = vec3_subs(ray->origin, sphere->center);
    double a = vec3_dot(ray->direction, ray->direction);
    double half_b = vec3_dot(oc, ray->direction);
    double c = vec3_dot(oc, oc) - sphere->r * sphere->r;
    double discriminant = half_b*half_b - a*c;
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
    rec->hit_point = rayAt(ray, rec->t);
    rec->N = vec3_division(vec3_subs(rec->hit_point, sphere->center), sphere->r); 
    set_face_normal(ray, rec);
    rec->t_max = rec->t;
	return (true);
}
