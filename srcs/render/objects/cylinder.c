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

static t_cy_cal	init_var(t_ray *ray, t_cylinder *cyl)
{
	t_cy_cal		cal;
	double			dot_ray_cy;
	double			dot_oc_cy;

	cal.hit_body = false;
	cal.hit_caps = false;
	dot_ray_cy = vec3_dot(ray->direction, cyl->n);
	cal.oc = vec3_subs(ray->origin, cyl->pos);
	dot_oc_cy = vec3_dot(cal.oc, cyl->n);
	cal.a = vec3_sqrd_len(ray->direction) - (dot_ray_cy * dot_ray_cy);
	cal.half_b = vec3_dot(ray->direction, cal.oc) - (dot_ray_cy * dot_oc_cy);
	cal.c = vec3_sqrd_len(cal.oc) - (cyl->r * cyl->r) - (dot_oc_cy * dot_oc_cy);
	cal.discr = cal.half_b * cal.half_b - cal.a * cal.c;
	return (cal);
}

static void	hit_cylinder_aux2(t_cy_cal *cal, t_ray *ray, t_cylinder *cyl, \
	t_hit_record *rec_body)
{
	cal->hit_point = ray_at(ray, cal->root);
	cal->height = vec3_dot(vec3_subs(cal->hit_point, cyl->pos), cyl->n);
	if (cal->height >= 0 && cal->height <= cyl->h)
	{
		rec_body->t = cal->root;
		rec_body->hit_point = cal->hit_point;
		rec_body->n = vec3_norm(vec3_subs(rec_body->hit_point, \
			vec3_add(cyl->pos, vec3_mult(cyl->n, \
			vec3_dot(vec3_subs(rec_body->hit_point, cyl->pos), cyl->n)))));
		set_face_normal(ray, rec_body);
		rec_body->t_max = rec_body->t;
		rec_body->color = cyl->color;
	}
	else
		cal->hit_body = false;
}

static void	hit_cylinder_aux(t_cy_cal *cal, t_ray *ray, t_cylinder *cyl, \
	t_hit_record *rec_body)
{
	cal->root = (-cal->half_b - sqrt(cal->discr)) / cal->a;
	if (cal->root < rec_body->t_min || cal->root > rec_body->t_max)
	{
		cal->root = (-cal->half_b + sqrt(cal->discr)) / cal->a;
		if (cal->root >= rec_body->t_min && cal->root <= rec_body->t_max)
			cal->hit_body = true;
	}
	else
		cal->hit_body = true;
	if (cal->hit_body)
		hit_cylinder_aux2(cal, ray, cyl, rec_body);
}

bool	hit_cylinder(t_object_list *obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder		*cyl;
	t_cy_cal		cal;
	t_hit_record	rec_body;
	t_hit_record	rec_caps;

	cyl = (t_cylinder *)obj->obj;
	cal = init_var(ray, cyl);
	rec_body = *rec;
	rec_caps = *rec;
	if (cal.discr >= 0)
		hit_cylinder_aux(&cal, ray, cyl, &rec_body);
	cal.hit_caps = hit_cylinder_caps(cyl, ray, &rec_caps);
	if (cal.hit_body && cal.hit_caps && rec_body.t < rec_caps.t)
		*rec = rec_body;
	else if (cal.hit_body && cal.hit_caps)
		*rec = rec_caps;
	else if (cal.hit_body)
		*rec = rec_body;
	else if (cal.hit_caps)
		*rec = rec_caps;
	else
		return (false);
	return (true);
}
