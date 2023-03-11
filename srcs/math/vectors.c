/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:03:32 by cmarcu            #+#    #+#             */
/*   Updated: 2023/03/11 17:27:12 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vectors.h"
#include "vectors.h"

t_vec3 vctor(double x, double y, double z)
{
	t_vec3 result;
	
	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}
int	equal(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	else
		return (0);
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
	double magnitude;
	t_vec3 result;

	magnitude = vec3_magnitude(a);
	result.x = a.x / magnitude;
	result.y = a.y / magnitude;
	result.z = a.z / magnitude;
	return (result);
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
		
// t_vec3	hadamard_product(t_vec3 c1, t_vec3 c2)
// {
// 	t_vec3 result;

// 	result.x = c1.x * c2.x;
// 	result.y = c1.y * c2.y;
// 	result.z = c1.z * c2.z;
// 	return (result);
// }
