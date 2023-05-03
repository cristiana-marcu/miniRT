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

#ifndef RAYS_H
# define RAYS_H

#include <math.h>
#include "canvas.h"
#include "vectors.h"
#include "objects.h"

t_ray	rctor(t_vec3 origin, t_vec3 direction);
t_vec3	ray_color(t_ray *r, t_world *world);
t_vec3	ray_at(t_ray *r, double pointOnRay);
void shoot_ray(t_data *data, t_ray *ray, t_vec3 *aux);

double	degree_to_radian(double degree);

void	set_face_normal(t_ray *ray, t_hit_record *rec);
t_sphere *new_sphere(t_vec3 center, double r, t_vec3 color);
bool hit_sphere(t_object_list *obj, t_ray *ray,t_hit_record *rec);

#endif
