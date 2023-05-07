/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:29:31 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/07 14:16:31 by cmarcu           ###   ########.fr       */
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

