/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:03:32 by cmarcu            #+#    #+#             */
/*   Updated: 2021/04/22 11:08:56 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_math.h"

int	equal(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	else
		return (0);
}

void	vec3_add(t_vec3 result, t_vec3 a, t_vec3 b)
{
	result[0] = a[0] + b[0];
	result[1] = a[1] + b[1];
	result[2] = a[2] + b[2];
}

void	vec3_subs(t_vec3 result, t_vec3 a, t_vec3 b)
{
	result[0] = a[0] - b[0];
	result[1] = a[1] - b[1];
	result[2] = a[2] - b[2];
}

void	vec3_negate(t_vec3 a)
{
	a[0] = -a[0];
	a[1] = -a[1];
	a[2] = -a[2];
}

void	vec3_mult(t_vec3 result, t_vec3 a, double n)
{
	result[0] = a[0] * n;
	result[1] = a[1] * n;
	result[2] = a[2] * n;
}

double	vec3_magnitude(t_vec3 a)
{
	return (sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]));
}

void	vec3_normalize(t_vec3 result, t_vec3 a)
{
	double magnitude;

	magnitude = vec3_magnitude(a);
	result[0] = a[0] / magnitude;
	result[1] = a[1] / magnitude;
	result[2] = a[2] / magnitude;
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

void	vec3_cross(t_vec3 result, t_vec3 a, t_vec3 b)
{
	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = a[2] * b[0] - a[0] * b[2];
	result[2] = a[0] * b[1] - a[1] * b[0];
}

void	hadamard_product(t_vec3 result, t_vec3 c1, t_vec3 c2)
{
	result[0] = c1[0] * c2[0];
	result[1] = c1[1] * c2[1];
	result[2] = c1[2] * c2[2];
}
