/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:15:05 by cristianama       #+#    #+#             */
/*   Updated: 2023/03/15 20:50:39 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>

double hit_sphere(t_vec3 center, double radius, const t_ray r) {
    t_vec3 oc = vec3_subs(r.origin, center);
    double a = vec3_dot(r.direction, r.direction);
    double b = 2.0 * vec3_dot(oc, r.direction);
    double c = vec3_dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0.0)
        return (-1.0);
    double solution = fabs((-b - sqrt(discriminant)) / (2.0 * a));
	return (solution);
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

t_vec3 ray_color(t_ray *r)
{
    double hitP;
    t_vec3 N;
    
    hitP = hit_sphere(vctor(0,0,-1), 0.5, *r);
    if (hitP > 0.0)
    {
        N = vec3_normalize(vec3_subs(rayAt(r, hitP), vctor(0, 0, -1)));
        return (vec3_mult(vctor(N.x + 1, N.y + 1, N.z + 1), 0.789));
    }
    t_vec3 unit_direction = vec3_normalize(r->direction);
    hitP = 0.5*(unit_direction.y + 1.0);
    return vec3_add(vec3_mult(vctor(1.0, 1.0, 1.0), (1.0-hitP)), vec3_mult(vctor(0.5, 0.7, 1.0), hitP));
}
