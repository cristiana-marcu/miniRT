/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:51:40 by cmarcu            #+#    #+#             */
/*   Updated: 2023/04/18 17:57:30 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "canvas.h"

t_cylinder *new_cylinder(t_vec3 pos, t_vec3 N, double r, t_vec3 color)
{
	t_cylinder *cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->pos = pos;
	cylinder->r = r;
	cylinder->color  = color;
	return (cylinder);
}

bool hit_cylinder(t_object_list *obj, t_ray *ray,t_hit_record *rec)
{
	t_cylinder *cylinder;
	double denominator;
	double t;

	cylinder = (t_cylinder*)obj->obj;
	
	return (true);
}