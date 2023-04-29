/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:51:40 by cmarcu            #+#    #+#             */
/*   Updated: 2023/04/29 17:59:42 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "canvas.h"

t_cylinder *new_cylinder(t_vec3 pos, t_vec3 N, double r, double H, t_vec3 color)
{
	t_cylinder *cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->pos = pos;
	cylinder->N = vec3_normalize(N);
	cylinder->r = r;
    cylinder->H = H;
	cylinder->color  = color;
	return (cylinder);
}

bool hit_cylinder_caps(t_cylinder *cyl, t_ray *ray, t_hit_record *rec)
{
    double t_cap;
    bool hit_cap = false;

    // Check intersection with top cap
    t_cap = (cyl->pos.y + cyl->H) - ray->origin.y;
    if (fabs(vec3_dot(cyl->N, ray->direction)) > 0.0001)
    {
        double t = t_cap / vec3_dot(cyl->N, ray->direction);
        t_vec3 hit_point = rayAt(ray, t);

        if (pow(hit_point.x - cyl->pos.x, 2) + pow(hit_point.z - cyl->pos.z, 2) <= pow(cyl->r, 2) && t > 0 && t < rec->t)
        {
            t_cap = t;
            hit_cap = true;
        }
    }

    // Check intersection with bottom cap 
    t_cap = (cyl->pos.y - ray->origin.y);
    if (fabs(vec3_dot(cyl->N, ray->direction)) > 0.0001)
    {
        double t = t_cap / vec3_dot(cyl->N, ray->direction);
        t_vec3 hit_point = rayAt(ray, t);

        if (pow(hit_point.x - cyl->pos.x, 2) + pow(hit_point.z - cyl->pos.z, 2) <= pow(cyl->r, 2) && t > 0 && t < rec->t)
        {
            if (hit_cap)
            {
                if (t < t_cap)
                    t_cap = t;
            }
            else
            {
                t_cap = t;
                hit_cap = true;
            }
        }
    }

    if (!hit_cap)
        return false;

    if (t_cap < rec->t_min || t_cap > rec->t_max)
        return false;
    return true;
}


bool hit_cylinder(t_object_list *obj, t_ray *ray, t_hit_record *rec)
{
    t_cylinder *cyl = (t_cylinder*)obj->obj;
    double		dot_ray_cy;
	double		dot_oc_cy;

    t_vec3 co = vec3_subs(ray->origin, cyl->pos);
    dot_ray_cy = vec3_dot(ray->direction, cyl->N);
	dot_oc_cy = vec3_dot(co, cyl->N);
    double a = vec3_sqrd_length(ray->direction) - (dot_ray_cy * dot_ray_cy);
    double half_b = vec3_dot(ray->direction, co) - (dot_ray_cy * dot_oc_cy);
    double c = vec3_sqrd_length(co) - (cyl->r * cyl->r) - (dot_oc_cy * dot_oc_cy);
    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return (false);
    double root = (-half_b - sqrt(discriminant)) / a;
    if (root < rec->t_min || root > rec->t_max)
    {
        root = (-half_b + sqrt(discriminant)) / a;
        if (root < rec->t_min || root > rec->t_max)
            return (false);
    }
    t_vec3 hit_point = rayAt(ray, root);
    double height = vec3_dot(vec3_subs(hit_point, cyl->pos), cyl->N);
    if (height < 0 || height > cyl->H)
        return (false);   
    // if (!(hit_cylinder_caps(cyl, ray, rec)))
    //     return (false); 
      
    rec->t = root;
    rec->hit_point = hit_point;
    rec->N = vec3_normalize(vec3_subs(rec->hit_point, vec3_add(cyl->pos, vec3_mult(cyl->N, vec3_dot(vec3_subs(rec->hit_point, cyl->pos), cyl->N)))));
    set_face_normal(ray, rec);
    rec->t_max = rec->t;

    return (true);
}
