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
