/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:02:03 by cmarcu            #+#    #+#             */
/*   Updated: 2023/03/25 18:03:29 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "vectors.h"
#include "ray.h"
#include "../srcs/libft/libft.h"

typedef struct s_object_list t_object_list;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
    LIGHT
}			t_type;

typedef struct s_sphere
{
    t_vec3 center;
    double r;
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

typedef struct s_hit_record
{
    t_vec3 hit_point;
    t_vec3 N;
    double t;
    bool front_face;
    double t_min;
    double t_max;
} t_hit_record;

typedef struct s_world
{
    t_object_list *objs;
    t_object_list *lights;
    t_ambientLight AL;
    t_camera camera;
    t_hit_record *rec;
} t_world;

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;
} t_ray;

typedef bool (*t_intersection_function)(t_object_list *, t_ray *, t_hit_record *);

struct s_object_list
{
    t_type type;
    void *obj;
    void *next;
};

bool hit_sphere(t_object_list *obj, t_ray *r,t_hit_record *rec);

#endif