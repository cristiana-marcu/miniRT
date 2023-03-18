/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:57:33 by cristianama       #+#    #+#             */
/*   Updated: 2023/03/18 19:01:18 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

#include <math.h>
#include "vectors.h"

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;
} t_ray;

typedef struct s_hit
{
    t_vec3 pos;
    t_vec3 N;
    double t; //t parameter of ray equation x + tP
    
} t_hit;

t_ray	rctor(t_vec3 origin, t_vec3 direction);
t_vec3	ray_color(t_ray *r);
t_vec3	rayAt(t_ray *r, double pointOnRay);

#endif