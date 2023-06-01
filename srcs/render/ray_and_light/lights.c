/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:29:31 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/15 13:38:46 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "ray.h"
#include <stdbool.h>
#include <stdio.h>

t_vec3	ambient_light_on_obj(t_world *world)
{
	t_vec3			amb_and_obj;
	t_ambientLight	al;

	al = world->amb_light;
	amb_and_obj = vctor(al.range * (al.color.x) * (world->rec->color.x), \
		al.range * (al.color.y) * (world->rec->color.y), \
		al.range * (al.color.z) * (world->rec->color.z));
	return (amb_and_obj);
}

t_vec3	diffuse_light_on_obj(t_world *world, t_ray shadow_ray)
{
	t_vec3	diffuse;
	double	dot_nl;

	dot_nl = vec3_dot(vec3_norm(world->rec->n),
			vec3_norm(shadow_ray.direction));
	if (dot_nl < 0)
		dot_nl = 0;
	diffuse.x = world->light.brightness * world->rec->color.x * dot_nl;
	diffuse.y = world->light.brightness * world->rec->color.y * dot_nl;
	diffuse.z = world->light.brightness * world->rec->color.z * dot_nl;
	return (diffuse);
}
