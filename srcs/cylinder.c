/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:51:40 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/29 20:35:09 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "canvas.h"

bool	hit_cylinder_caps(t_cylinder *cyl, t_ray *ray, t_hit_record *rec_caps)
{
	bool hit = false;
	int	i;
	// Para cada tapa (inferior y superior)
	i = -1;
	while (++i < 2)
	{
		// Calcular el valor t para la intersección con el plano de la tapa
		double t = (vec3_dot(vec3_subs(vec3_add(cyl->pos, vec3_mult(cyl->n, cyl->h * i)), ray->origin), cyl->n)) / vec3_dot(ray->direction, cyl->n);
		if (t < rec_caps->t_min || t > rec_caps->t_max)
			continue;
		t_vec3 hit_point = ray_at(ray, t);
		// Comprobar si el punto de intersección está dentro del círculo de la tapa
		if (vec3_sqrd_len(vec3_subs(hit_point, vec3_add(cyl->pos, vec3_mult(cyl->n, cyl->h * i)))) > (cyl->r * cyl->r))
			continue;
		rec_caps->t = t;
		rec_caps->hit_point = hit_point;
		rec_caps->n = cyl->n;
		set_face_normal(ray, rec_caps);
		rec_caps->t_max = rec_caps->t;
		rec_caps->color = cyl->color;
		hit = true;
	}
	return hit;
}

bool hit_cylinder(t_object_list *obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cyl;
	double		dot_ray_cy;
	double		dot_oc_cy;
	bool        hit_body = false;
	bool        hit_caps = false;

	cyl = (t_cylinder*)obj->obj;
	t_vec3 co = vec3_subs(ray->origin, cyl->pos);
	dot_ray_cy = vec3_dot(ray->direction, cyl->n);
	dot_oc_cy = vec3_dot(co, cyl->n);

	double a = vec3_sqrd_len(ray->direction) - (dot_ray_cy * dot_ray_cy);
	double half_b = vec3_dot(ray->direction, co) - (dot_ray_cy * dot_oc_cy);
	double c = vec3_sqrd_len(co) - (cyl->r * cyl->r) - (dot_oc_cy * dot_oc_cy);
	double discriminant = half_b * half_b - a * c;

	t_hit_record rec_body = *rec;
	t_hit_record rec_caps = *rec;

	if (discriminant >= 0)
	{
		double root = (-half_b - sqrt(discriminant)) / a;
		if (root < rec_body.t_min || root > rec_body.t_max)
		{
			root = (-half_b + sqrt(discriminant)) / a;
			if (root >= rec_body.t_min && root <= rec_body.t_max)
				hit_body = true;
		}
		else
			hit_body = true;
		if (hit_body)
		{
			t_vec3 hit_point = ray_at(ray, root);
			double height = vec3_dot(vec3_subs(hit_point, cyl->pos), cyl->n);
			if (height >= 0 && height <= cyl->h)
			{
				rec_body.t = root;
				rec_body.hit_point = hit_point;
				rec_body.n = vec3_norm(vec3_subs(rec_body.hit_point, vec3_add(cyl->pos, vec3_mult(cyl->n, vec3_dot(vec3_subs(rec_body.hit_point, cyl->pos), cyl->n)))));
				set_face_normal(ray, &rec_body);
				rec_body.t_max = rec_body.t;
				rec_body.color = cyl->color;
			}
			else
				hit_body = false;
		}
	}
	hit_caps = hit_cylinder_caps(cyl, ray, &rec_caps);
	if (hit_body && hit_caps)
	{
		if (rec_body.t < rec_caps.t)
			*rec = rec_body;
		else
			*rec = rec_caps;
	}
	else if (hit_body)
		*rec = rec_body;
	else if (hit_caps)
		*rec = rec_caps;
	else
		return false;
	return true;
}
