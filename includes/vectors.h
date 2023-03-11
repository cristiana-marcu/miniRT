/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:00:37 by cmarcu            #+#    #+#             */
/*   Updated: 2023/03/11 17:30:56 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

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

t_vec3	vctor(double x, double y, double z);
int	equal(double a, double b);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_subs(t_vec3 a, t_vec3 b);
t_vec3	vec3_negate(t_vec3 a);
t_vec3	vec3_mult(t_vec3 a, double n);
t_vec3	vec3_division(t_vec3 a, double n) ;
double	vec3_magnitude(t_vec3 a);
t_vec3	vec3_normalize(t_vec3 a);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	length(t_vec3 e);
double	length_squared(t_vec3 e);

//t_vec3	hadamard_product(t_vec3 c1, t_vec3 c2);

#endif