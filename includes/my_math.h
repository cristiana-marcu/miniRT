/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:00:37 by cmarcu            #+#    #+#             */
/*   Updated: 2021/04/22 11:18:04 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MATH_H
# define MY_MATH_H

#include <math.h>

# ifndef EPSILON
#  define EPSILON 0.00001
# endif

typedef struct	s_vec3
{
	double x;
	double y;
	double z;
}				t_vec3;

typedef struct	s_mat44
{
	double d[4][4];
}				t_mat44;

typedef struct	s_mat33
{
	double d[3][3];
}				t_mat33;

int	equal(double a, double b);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_subs(t_vec3 a, t_vec3 b);
t_vec3	vec3_negate(t_vec3 a);
t_vec3	vec3_mult(t_vec3 a, double n);
double	vec3_magnitude(t_vec3 a);
t_vec3	vec3_normalize(t_vec3 a);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
t_vec3	hadamard_product(t_vec3 c1, t_vec3 c2);

#endif
