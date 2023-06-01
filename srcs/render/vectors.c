/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:03:32 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/09 20:11:16 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec3	vctor(double x, double y, double z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

double	equal(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	else
		return (false);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec3	vec3_subs(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec3	vec3_negate(t_vec3 a)
{
	t_vec3	result;

	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;
	return (result);
}

t_vec3	vec3_mult(t_vec3 a, double n)
{
	t_vec3	result;

	result.x = a.x * n;
	result.y = a.y * n;
	result.z = a.z * n;
	return (result);
}

t_vec3	vec3_div(t_vec3 a, double n)
{
	t_vec3	result;

	result = vec3_mult(a, 1 / n);
	return (result);
}

double	vec3_sqrd_len(t_vec3 a)
{
	return ((a.x * a.x + a.y * a.y + a.z * a.z));
}

double	vec3_magn(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	vec3_norm(t_vec3 a)
{
	return (vec3_div(a, vec3_magn(a)));
}

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

int	vec3_to_rgb(t_vec3 v)
{
	int		samples_per_pixel;
	double	scale;

	/*_________Antialiasing shit__________*
	samples_per_pixel = 100;
	scale = 1.0 / samples_per_pixel;
	v.x *= scale;
	v.y *= scale;
	v.z *= scale;
	*_____________________________________*/
	return ((int)(v.x * 255.999) << 16 | (int)(v.y * 255.999) << 8 | (int)(v.z
			* 255.999));
	//Con esta solución aparece la línea blanca rara en las esferas al sombrear
}

t_vec3	clamp_color(t_vec3 color)
{
	t_vec3	clamped_color;

	clamped_color.x = fmin(fmax(color.x, 0.0), 1);
	clamped_color.y = fmin(fmax(color.y, 0.0), 1);
	clamped_color.z = fmin(fmax(color.z, 0.0), 1);
	return (clamped_color);
}
