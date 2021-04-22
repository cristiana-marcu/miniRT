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

typedef double t_vec3[3];
typedef double t_mat44[4][4];

int	equal(double a, double b);
void	vec3_add(t_vec3 result, t_vec3 a, t_vec3 b);
void	vec3_subs(t_vec3 result, t_vec3 a, t_vec3 b);
void	vec3_negate(t_vec3 a);
void	vec3_mult(t_vec3 result, t_vec3 a, double n);
double	vec3_magnitude(t_vec3 a);
void	vec3_normalize(t_vec3 result, t_vec3 a);
double	vec3_dot(t_vec3 a, t_vec3 b);
void	vec3_cross(t_vec3 result, t_vec3 a, t_vec3 b);
void	hadamard_product(t_vec3 result, t_vec3 c1, t_vec3 c2);

#endif
