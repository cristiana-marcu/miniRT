/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:00:37 by cmarcu            #+#    #+#             */
/*   Updated: 2023/06/03 13:01:41 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */
# include <math.h>
# include <stdbool.h>

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */
# ifndef EPSILON
#  define EPSILON 0.00001
# endif

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
t_vec3		vctor(double x, double y, double z);
double		equal(double a, double b);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_subs(t_vec3 a, t_vec3 b);
t_vec3		vec3_negate(t_vec3 a);
t_vec3		vec3_mult(t_vec3 a, double n);
t_vec3		vec3_div(t_vec3 a, double n);
double		vec3_sqrd_len(t_vec3 a);
double		vec3_magn(t_vec3 a);
t_vec3		vec3_norm(t_vec3 a);
double		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
int			vec3_to_rgb(t_vec3 v);
t_vec3		clamp_color(t_vec3 color);
bool		vec3_along_y_axis(t_vec3 a);

#endif
