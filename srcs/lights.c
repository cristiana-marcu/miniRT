/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:29:31 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/07 16:03:42 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "canvas.h"

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

