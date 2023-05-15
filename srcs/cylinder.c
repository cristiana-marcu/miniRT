/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:51:40 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/15 16:22:54 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "canvas.h"

t_cylinder	*new_cylinder(t_vec3 pos, t_vec3 N, double r, double H, t_vec3 color)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->pos = pos;
	cylinder->N = vec3_norm(N);
	cylinder->r = r;
	cylinder->H = H;
	cylinder->color  = color;
	return (cylinder);
}

bool	hit_cylinder_caps(t_cylinder *cyl, t_ray *ray, t_hit_record *rec_caps)
{
	bool hit = false;
	// Para cada tapa (inferior y superior)
	for (int i = 0; i < 2; ++i) {
		// Calcular el valor t para la intersección con el plano de la tapa
		double t = (vec3_dot(vec3_subs(vec3_add(cyl->pos, vec3_mult(cyl->N, cyl->H * i)), ray->origin), cyl->N)) / vec3_dot(ray->direction, cyl->N);

		// Si t está dentro del rango válido
		if (t < rec_caps->t_min || t > rec_caps->t_max)
			continue;

		// Calcular el punto de intersección
		t_vec3 hit_point = ray_at(ray, t);

		// Comprobar si el punto de intersección está dentro del círculo de la tapa
		if (vec3_sqrd_len(vec3_subs(hit_point, vec3_add(cyl->pos, vec3_mult(cyl->N, cyl->H * i)))) > (cyl->r * cyl->r))
			continue;

		// Actualizar el registro de la intersección
		rec_caps->t = t;
		rec_caps->hit_point = hit_point;
		rec_caps->N = cyl->N;
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
	dot_ray_cy = vec3_dot(ray->direction, cyl->N);
	dot_oc_cy = vec3_dot(co, cyl->N);

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
			double height = vec3_dot(vec3_subs(hit_point, cyl->pos), cyl->N);

			if (height >= 0 && height <= cyl->H)
			{
				rec_body.t = root;
				rec_body.hit_point = hit_point;
				rec_body.N = vec3_norm(vec3_subs(rec_body.hit_point, vec3_add(cyl->pos, vec3_mult(cyl->N, vec3_dot(vec3_subs(rec_body.hit_point, cyl->pos), cyl->N)))));
				set_face_normal(ray, &rec_body);
				rec_body.t_max = rec_body.t;
				rec_body.color = cyl->color;
			}
			else
			{
				hit_body = false;
			}
		}
	}

	hit_caps = hit_cylinder_caps(cyl, ray, &rec_caps);

	// If we hit both, we want to take the closest hit.
	if (hit_body && hit_caps)
	{
		if (rec_body.t < rec_caps.t)
			*rec = rec_body;
		else
			*rec = rec_caps;
	}
	else if (hit_body)
	{
		*rec = rec_body;
	}
	else if (hit_caps)
	{
		*rec = rec_caps;
	}
	else
	{
		return false;
	}

	return true;
}


// // Función para comprobar la intersección con las tapas del cilindro
// bool hit_cylinder_caps(t_cylinder *cyl, t_ray *ray, t_hit_record *rec)
// {
// 	bool hit = false;
// 	t_hit_record temp_rec;
// 	temp_rec.t = rec->t_max;

// 	for (int i = 0; i < 2; ++i) {
// 		double t = (vec3_dot(vec3_subs(vec3_add(cyl->pos, vec3_mult(cyl->N, cyl->H * i)), ray->origin), cyl->N)) / vec3_dot(ray->direction, cyl->N);
// 		if (t < rec->t_min || t > rec->t_max || t > temp_rec.t) continue;

// 		t_vec3 hit_point = ray_at(ray, t);
// 		if (vec3_sqrd_len(vec3_subs(hit_point, vec3_add(cyl->pos, vec3_mult(cyl->N, cyl->H * i)))) > (cyl->r * cyl->r)) continue;

// 		temp_rec.t = t;
// 		temp_rec.hit_point = hit_point;
// 		temp_rec.N = cyl->N;
// 		set_face_normal(ray, &temp_rec);
// 		temp_rec.color = cyl->color;
// 		hit = true;
// 	}

// 	if (hit) *rec = temp_rec;
// 	return hit;
// }

// // Función para comprobar la intersección con el cuerpo del cilindro
// bool hit_cylinder_body(t_cylinder *cyl, t_ray *ray, t_hit_record *rec)
// {
// 	t_vec3 co = vec3_subs(ray->origin, cyl->pos);
// 	double dot_ray_cy = vec3_dot(ray->direction, cyl->N);
// 	double dot_oc_cy = vec3_dot(co, cyl->N);
// 	double a = vec3_sqrd_len(ray->direction) - (dot_ray_cy * dot_ray_cy);
// 	double half_b = vec3_dot(ray->direction, co) - (dot_ray_cy * dot_oc_cy);
// 	double c = vec3_sqrd_len(co) - (cyl->r * cyl->r) - (dot_oc_cy * dot_oc_cy);
// 	double discriminant = half_b * half_b - a * c;

// 	if (discriminant < 0) return false;

// 	double root = (-half_b - sqrt(discriminant)) / a;
// 	if (root < rec->t_min || root > rec->t_max)
// 	{
// 		root = (-half_b + sqrt(discriminant)) / a;
// 		if (root < rec->t_min || root > rec->t_max)
// 			return false;
// 	}

// 	t_vec3 hit_point = ray_at(ray, root);
// 	double height = vec3_dot(vec3_subs(hit_point, cyl->pos), cyl->N);
// 	if (height < 0 || height > cyl->H) return false;

// 	rec->t = root;
// 	rec->hit_point = hit_point;
// 	rec->N = vec3_norm(vec3_subs(rec->hit_point, vec3_add(cyl->pos, vec3_mult(cyl->N, vec3_dot(vec3_subs(rec->hit_point, cyl->pos), cyl->N)))));
// 	set_face_normal(ray, rec);
// 	rec->color = cyl->color;
// 	return true;
// }

// // Función principal para comprobar la intersección con el cilindro
// bool hit_cylinder(t_object_list *obj, t_ray *ray, t_hit_record *rec)
// {
// 	t_cylinder *cyl = (t_cylinder*)obj->obj;
// 	t_hit_record temp_rec_body, temp_rec_caps = *rec;
// 	temp_rec_body.t = temp_rec_caps.t = rec->t_max;

// 	bool hit_body = hit_cylinder_body(cyl, ray, &temp_rec_body);
// 	bool hit_caps = hit_cylinder_caps(cyl, ray, &temp_rec_caps);

// 	if (!hit_body && !hit_caps) return false;

// 	if (temp_rec_body.t < temp_rec_caps.t) {
// 		rec->t = temp_rec_body.t;
// 		rec->hit_point = temp_rec_body.hit_point;
// 		rec->N = temp_rec_body.N;
// 		rec->t_max = temp_rec_body.t_max;
// 		rec->color = temp_rec_body.color;
// 	} else {
// 		rec->t = temp_rec_caps.t;
// 		rec->hit_point = temp_rec_caps.hit_point;
// 		rec->N = temp_rec_caps.N;
// 		rec->t_max = temp_rec_caps.t_max;
// 		rec->color = temp_rec_caps.color;
// 	}

// 	return true;
// }
