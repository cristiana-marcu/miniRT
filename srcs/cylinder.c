/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:51:40 by cmarcu            #+#    #+#             */
/*   Updated: 2023/04/26 21:14:53 by cmarcu           ###   ########.fr       */
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

bool hit_cylinder(t_object_list *obj, t_ray *ray, t_hit_record *rec)
{
    t_cylinder *cyl = (t_cylinder*)obj->obj;

    t_vec3 co = vec3_subs(ray->origin, cyl->pos);
    double a = vec3_dot(ray->direction, ray->direction) - pow(vec3_dot(ray->direction, cyl->N), 2);
    double b = 2 * (vec3_dot(ray->direction, co) - vec3_dot(ray->direction, cyl->N) * vec3_dot(co, cyl->N));
    double c = vec3_dot(co, co) - pow(vec3_dot(co, cyl->N), 2) - pow(cyl->r, 2);

    double delta = b * b - 4 * a * c;

    if (delta < 0)
        return (false);

    double t1 = (-b + sqrt(delta)) / (2 * a);
    double t2 = (-b - sqrt(delta)) / (2 * a);

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

    if (t_closest < rec->t_min || t_closest > rec->t_max)
    {
        if (t_farthest < rec->t_min || t_farthest > rec->t_max)
            return (false);
        t_closest = t_farthest;
    }

    t_vec3 hit_point = rayAt(ray, t_closest);
    double height = vec3_dot(vec3_subs(hit_point, cyl->pos), cyl->N);
    if (height < 0 || height > cyl->H)
        return (false);
    
    rec->t = t_closest;
    rec->hit_point = hit_point;
    rec->N = vec3_normalize(vec3_subs(rec->hit_point, vec3_add(cyl->pos, vec3_mult(cyl->N, vec3_dot(vec3_subs(rec->hit_point, cyl->pos), cyl->N)))));
    set_face_normal(ray, rec);
    rec->t_max = rec->t;

    return (true);
}
