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

#include "canvas.h"
#include "objects.h"
#include "ray.h"
#include <stdbool.h>
#include <stdio.h>

t_light	*new_light(t_vec3 pos, double brightness, t_vec3 color)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->pos = pos;
	light->brightness = brightness;
	light->color = color;
	return (light);
}

t_ambientLight	*new_ambient_light(double range, t_vec3 color)
{
	t_ambientLight	*al;

	al = malloc(sizeof(t_ambientLight));
	if (!al)
		return (NULL);
	al->range = range;
	al->color = color;
	return (al);
}

t_vec3	ambient_light_on_obj(t_world *world)
{
	t_vec3			amb_and_obj;
	t_ambientLight	al;

	al = world->amb_light;
	amb_and_obj = vctor(al.range * (al.color.x) * (world->rec->color.x),
						al.range * (al.color.y) * (world->rec->color.y),
						al.range * (al.color.z) * (world->rec->color.z));
	return (amb_and_obj);
}

t_vec3	diffuse_light_on_obj(t_world *world, t_ray shadow_ray)
{
	t_vec3	diffuse;
	double	dot_NL;

	dot_NL = vec3_dot(vec3_norm(world->rec->n),
			vec3_norm(shadow_ray.direction));
	if (dot_NL < 0)
		dot_NL = 0;
	diffuse.x = world->light.brightness * world->rec->color.x * dot_NL;
	diffuse.y = world->light.brightness * world->rec->color.y * dot_NL;
	diffuse.z = world->light.brightness * world->rec->color.z * dot_NL;
	return (diffuse);
}
