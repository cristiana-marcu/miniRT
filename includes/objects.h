/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:02:03 by cmarcu            #+#    #+#             */
/*   Updated: 2023/03/18 19:23:46 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "vectors.h"
#include "ray.h"
#include "../srcs/libft/libft.h"

typedef struct s_object t_object;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}			t_type;

typedef struct s_sphere
{
    t_vec3 center;
    double D;
    t_vec3 color;
} t_sphere;

typedef struct s_plane
{
    t_vec3 pos;
    t_vec3 N;
    t_vec3 color;
} t_plane;

typedef struct s_cylinder
{
    t_vec3 pos;
    t_vec3 N;
    double D;
    double H;
    t_vec3 color;
} t_cylinder;

typedef struct s_ambientLight
{
    double range;
    t_vec3 color;
} t_ambientLight;

typedef struct s_light
{
    t_vec3 pos;
    double brightness;
    t_vec3 color; //solo bonus
} t_light;

typedef struct s_camera
{
    t_vec3 from;
    t_vec3 lookAt; //Normalized direction vector
    double HFOV;
} t_camera;

typedef bool (*t_intersection_function)(t_object *, t_ray *, t_hit *);

struct s_object
{
    t_type type;
    t_vec3 pos;
    t_vec3 color;
    t_intersection_function intersect;
};

typedef struct s_world
{
    t_list *objs;
    t_list *lights;
    t_ambientLight AL;
    t_camera camera;
} t_world;

double hit_sphere(t_vec3 center, double radius, const t_ray r);

#endif