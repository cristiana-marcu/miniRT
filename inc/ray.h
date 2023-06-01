/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:57:33 by cristianama       #+#    #+#             */
/*   Updated: 2023/05/03 14:04:27 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */
# include "objects.h"
# include <math.h>

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
t_vec3	vctor(double x, double y, double z);
t_ray	rctor(t_vec3 origin, t_vec3 direction);
t_vec3	ray_color(t_ray *r, t_world *world);
t_vec3	ray_at(t_ray *r, double pointOnRay);
void	shoot_ray(t_data *data, t_ray *ray, t_vec3 *aux);
void	set_face_normal(t_ray *ray, t_hit_record *rec);
bool	hit_sphere(t_object_list *obj, t_ray *ray, t_hit_record *rec);
bool	hit_cylinder_caps(t_cylinder *cyl, t_ray *ray, t_hit_record *rec_caps);

#endif
