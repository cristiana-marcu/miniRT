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

#include "objects.h"
#include "ray.h"
#include <stdbool.h>
#include <stdio.h>

static void	hit_cy_caps_aux(t_cylinder *cyl, t_ray *ray, t_hit_record *rec_caps)
{
	rec_caps->n = cyl->n;
	set_face_normal(ray, rec_caps);
	rec_caps->t_max = rec_caps->t;
	rec_caps->color = cyl->color;
}

bool	hit_cylinder_caps(t_cylinder *cyl, t_ray *ray, t_hit_record *rec_caps)
{
	bool	hit;
	int		i;
	double	t;
	t_vec3	hit_point;

	hit = false;
	i = -1;
	while (++i < 2)
	{
		t = (vec3_dot(vec3_subs(vec3_add(cyl->pos, vec3_mult(cyl->n, cyl->h \
			* i)), ray->origin), cyl->n)) / vec3_dot(ray->direction, cyl->n);
		if (t < rec_caps->t_min || t > rec_caps->t_max)
			continue ;
		hit_point = ray_at(ray, t);
		if (vec3_sqrd_len(vec3_subs(hit_point, vec3_add(cyl->pos, \
			vec3_mult(cyl->n, cyl->h * i)))) > (cyl->r * cyl->r))
			continue ;
		rec_caps->t = t;
		rec_caps->hit_point = hit_point;
		hit_cy_caps_aux(cyl, ray, rec_caps);
		hit = true;
	}
	return (hit);
}

static t_cy_cal init_var(t_ray *ray, t_cylinder *cyl)
{
	t_cy_cal		cal;
	double			dot_ray_cy;
	double			dot_oc_cy;

	dot_ray_cy = vec3_dot(ray->direction, cyl->n);
	cal.oc = vec3_subs(ray->origin, cyl->pos);
	dot_oc_cy = vec3_dot(cal.oc, cyl->n);
	cal.a = vec3_sqrd_len(ray->direction) - (dot_ray_cy * dot_ray_cy);
	cal.half_b = vec3_dot(ray->direction, cal.oc) - (dot_ray_cy * dot_oc_cy);
	cal.c = vec3_sqrd_len(cal.oc) - (cyl->r * cyl->r) - (dot_oc_cy * dot_oc_cy);
	cal.discr = cal.half_b * cal.half_b - cal.a * cal.c;
	return (cal);
}

bool	hit_cylinder(t_object_list *obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder		*cyl;
	t_cy_cal		cal;
	bool			hit_body;
	bool			hit_caps;
	t_hit_record	rec_body;
	t_hit_record	rec_caps;
	t_vec3			hit_point;

	hit_body = false;
	hit_caps = false;
	cyl = (t_cylinder *)obj->obj;
	cal = init_var(ray, cyl);
	rec_body = *rec;
	rec_caps = *rec;
	if (cal.discr >= 0)
	{
		cal.root = (-cal.half_b - sqrt(cal.discr)) / cal.a;
		if (cal.root < rec_body.t_min || cal.root > rec_body.t_max)
		{
			cal.root = (-cal.half_b + sqrt(cal.discr)) / cal.a;
			if (cal.root >= rec_body.t_min && cal.root <= rec_body.t_max)
				hit_body = true;
		}
		else
			hit_body = true;
		if (hit_body)
		{
			hit_point = ray_at(ray, cal.root);
			cal.height = vec3_dot(vec3_subs(hit_point, cyl->pos), cyl->n);
			if (cal.height >= 0 && cal.height <= cyl->h)
			{
				rec_body.t = cal.root;
				rec_body.hit_point = hit_point;
				rec_body.n = vec3_norm(vec3_subs(rec_body.hit_point,
							vec3_add(cyl->pos, vec3_mult(cyl->n,
									vec3_dot(vec3_subs(rec_body.hit_point,
											cyl->pos), cyl->n)))));
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
		return (false);
	return (true);
}
