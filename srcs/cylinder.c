/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:51:40 by cmarcu            #+#    #+#             */
/*   Updated: 2023/04/26 20:50:47 by cmarcu           ###   ########.fr       */
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

bool hit_cylinder(t_object_list *obj, t_ray *ray,t_hit_record *rec)
{
	t_cylinder *cyl;

	cyl = (t_cylinder*)obj->obj;
	
	t_vec3 p1p0 = vec3_subs(ray->origin, cyl->pos);
    t_vec3 VxN = vec3_cross(ray->direction, cyl->N);
    t_vec3 VxNxN = vec3_cross(VxN, cyl->N);
    double a = vec3_dot(VxNxN, VxNxN) / vec3_dot(cyl->N, cyl->N);
    double b = 2 * vec3_dot(VxNxN, vec3_cross(p1p0, cyl->N)) / vec3_dot(cyl->N, cyl->N);
    double c = (vec3_dot(vec3_cross(p1p0, cyl->N), vec3_cross(p1p0, cyl->N)) - (cyl->r * cyl->r)) / vec3_dot(cyl->N, cyl->N);
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (false);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);
    double t2 = (-b - sqrt(discriminant)) / (2 * a);
    double t_closest, t_farthest;
    if (t1 > t2)
    {
        t_closest = t2;
        t_farthest = t1;
    }
    else
    {
        t_closest = t1;
        t_farthest = t2;
    }
    t_vec3 point = rayAt(ray, t_closest);
    t_vec3 vec_from_base_to_point = vec3_subs(point, cyl->pos);
    double dist_to_cyl_axis_sq = vec3_dot(vec_from_base_to_point, vec_from_base_to_point) - pow(vec3_dot(vec_from_base_to_point, cyl->N), 2);
    if (dist_to_cyl_axis_sq > cyl->r * cyl->r || t_closest < rec->t_min || t_closest > rec->t_max)
    {
        point = rayAt(ray, t_farthest);
        vec_from_base_to_point = vec3_subs(point, cyl->pos); // Añade esta línea
        dist_to_cyl_axis_sq = vec3_dot(vec_from_base_to_point, vec_from_base_to_point) - pow(vec3_dot(vec_from_base_to_point, cyl->N), 2);
        if (dist_to_cyl_axis_sq > cyl->r * cyl->r || t_farthest < rec->t_min || t_farthest > rec->t_max)
            return (false);
        rec->t = t_farthest;
    }
    else
    {
        rec->t = t_closest;
    }
    point = rayAt(ray, rec->t);
    double height = vec3_dot(vec3_subs(point, cyl->pos), cyl->N);
    if (height < 0 || height > cyl->H)
        return (false);
    rec->hit_point = rayAt(ray, rec->t);
    rec->N = vec3_normalize(vec3_subs(rec->hit_point, vec3_add(cyl->pos, vec3_mult(cyl->N, height))));
    set_face_normal(ray, rec);
    rec->t_max = rec->t;
    return (true);
}