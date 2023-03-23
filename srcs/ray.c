/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:15:05 by cristianama       #+#    #+#             */
/*   Updated: 2023/03/23 14:04:01 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"

void	set_face_normal(t_ray *ray, t_hit_record *rec)
{
	rec->front_face = vec3_dot(ray->direction, rec->N) < 0;
	if (rec->front_face == false)
		rec->N = vec3_negate(rec->N);
}

bool hit_sphere(t_object_list *obj, t_ray *ray,t_hit_record *rec)
{
	t_sphere *sphere;

	sphere = (t_sphere*)obj;
	
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
	return (true);
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

t_vec3 ray_color(t_ray *r, t_world *world)
{
    double hitP;
    t_vec3 N;
    t_object_list *obj;
    
    world->rec->t_min = EPSILON;
    world->rec->t_max = INFINITY;
    
    obj = world->objs;
	while (obj)
    {
        if (obj->type == SPHERE)
            hitP = hit_sphere(obj->obj, r, world->rec); //Este casteo da problemas
            
        obj = obj->next;
    }
    if (hitP > 0.0)
    {
        N = vec3_normalize(vec3_subs(rayAt(r, hitP), vctor(0, 0, -1)));
        return (vec3_mult(vctor(N.x + 1, N.y + 1, N.z + 1), 0.789));
    }
    t_vec3 unit_direction = vec3_normalize(r->direction);
    hitP = 0.5*(unit_direction.y + 1.0);
    return vec3_add(vec3_mult(vctor(1.0, 1.0, 1.0), (1.0-hitP)), vec3_mult(vctor(0.5, 0.7, 1.0), hitP));
}
