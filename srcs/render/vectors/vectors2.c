/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:03:32 by cmarcu            #+#    #+#             */
/*   Updated: 2023/06/01 18:52:21 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

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
