/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:03:32 by cmarcu            #+#    #+#             */
/*   Updated: 2023/04/01 15:05:10 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec3 vctor(double x, double y, double z)
{
	t_vec3 result;
	
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
	t_vec3 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec3	vec3_subs(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec3	vec3_negate(t_vec3 a)
{
	t_vec3 result;

	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;
	return (result);
}

t_vec3	vec3_mult(t_vec3 a, double n)
{
	t_vec3 result;

	result.x = a.x * n;
	result.y = a.y * n;
	result.z = a.z * n;
	return (result);
}

t_vec3 vec3_division(t_vec3 a, double n)
{
	t_vec3 result;
	
	result = vec3_mult(a, 1/n);
	return (result);
}

double	vec3_magnitude(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	vec3_normalize(t_vec3 a)
{
	return (vec3_division(a, vec3_magnitude(a)));
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double length(t_vec3 e)
{
	return sqrt(length_squared(e));
}

double length_squared(t_vec3 e)
{
	return e.x*e.x + e.y*e.y + e.z*e.z;
}

double clamp(double x, double min, double max)
{
	if (x < min)
		return min;
	if (x > max)
		return max;
	return x;
}

int vec3_toRGB(t_vec3 v)
{
	/*_________Antialiasing shit__________*
	int samples_per_pixel;
	double scale;

	samples_per_pixel = 100;
	scale = 1.0 / samples_per_pixel;
	v.x *= scale;
	v.y *= scale;
	v.z *= scale;
	*_____________________________________*/
	return((int)(v.x * 255.999) << 16 | (int)(v.y * 255.999) << 8 | (int)(v.z * 255.999)); //Con esta solución aparece la línea blanca rara en las esferas al sombrear
}	
