/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:03:32 by cmarcu            #+#    #+#             */
/*   Updated: 2023/06/01 18:52:28 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3	clamp_color(t_vec3 color)
{
	t_vec3	clamped_color;

	clamped_color.x = fmin(fmax(color.x, 0.0), 1);
	clamped_color.y = fmin(fmax(color.y, 0.0), 1);
	clamped_color.z = fmin(fmax(color.z, 0.0), 1);
	return (clamped_color);
}

int	vec3_to_rgb(t_vec3 v)
{
	return ((int)(v.x * 255.999) << 16 | (int)(v.y * 255.999) << 8 | (int)(v.z
			* 255.999));
}
/*
vec3_to_rgb sin norma

int	vec3_to_rgb(t_vec3 v)
{
	int		samples_per_pixel;
	double	scale;

	*_________Antialiasing shit__________*
	samples_per_pixel = 100;
	scale = 1.0 / samples_per_pixel;
	v.x *= scale;
	v.y *= scale;
	v.z *= scale;
	*_____________________________________*
	return ((int)(v.x * 255.999) << 16 | (int)(v.y * 255.999) << 8 | (int)(v.z
			* 255.999));
	//Con esta solución aparece la línea blanca rara en las esferas al sombrear
}
*/
