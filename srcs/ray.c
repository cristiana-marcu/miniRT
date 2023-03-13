/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:15:05 by cristianama       #+#    #+#             */
/*   Updated: 2023/03/13 20:13:57 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>

bool hit_sphere(t_vec3 center, double radius, const t_ray r) {
    t_vec3 oc = vec3_subs(r.origin, center);
    double a = vec3_dot(r.direction, r.direction);
    double b = 2.0 * vec3_dot(oc, r.direction);
    double c = vec3_dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
	return (discriminant > 0);
}

t_ray rctor(t_vec3 origin, t_vec3 direction)
{
	t_ray r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_vec3 ray_color(t_ray *r) {
    if (hit_sphere(vctor(0,0,-1), 0.5, *r))
        return vctor(1, 0, 0);
    t_vec3 unit_direction = vec3_normalize(r->direction);
    double t = 0.5*(unit_direction.y + 1.0);
    return vec3_add(vec3_mult(vctor(1.0, 1.0, 1.0), (1.0-t)), vec3_mult(vctor(0.5, 0.7, 1.0), t));
}
