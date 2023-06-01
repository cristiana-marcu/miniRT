/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:02:03 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/10 07:26:40 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */
# include "mlx.h"
# include "libft.h"
# include "vectors.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */
# define K_ESC 53

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */
typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT
}			t_type;

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */
typedef struct s_object_list
{
	t_type						type;
	void						*obj;
	void						*next;
}						t_object_list;

typedef struct s_sphere
{
	t_vec3						center;
	double						r;
	t_vec3						color;
}								t_sphere;

typedef struct s_plane
{
	t_vec3						pos;
	t_vec3						n;
	t_vec3						color;
}								t_plane;

typedef struct s_cylinder
{
	t_vec3						pos;
	t_vec3						n;
	double						r;
	double						h;
	t_vec3						color;
}								t_cylinder;

typedef struct s_ambientLight
{
	double						range;
	t_vec3						color;
}								t_ambientLight;

typedef struct s_light
{
	t_vec3						pos;
	double						brightness;
	t_vec3						color;
}								t_light;

typedef struct s_camera
{
	t_vec3						from;
	t_vec3						lookat;
	double						hfov;
	double						viewport_height;
	double						viewport_width;
	t_vec3						w;
	t_vec3						u;
	t_vec3						v;
	t_vec3						horizontal;
	t_vec3						vertical;
	t_vec3						lower_left_corner;
}								t_camera;

typedef struct s_hit_record
{
	t_vec3						hit_point;
	t_vec3						n;
	double						t;
	bool						front_face;
	double						t_min;
	double						t_max;
	t_vec3						color;
}								t_hit_record;

typedef struct s_world
{
	t_object_list				*objs;
	t_light						light;
	t_ambientLight				amb_light;
	t_camera					camera;
	t_hit_record				*rec;
}								t_world;

typedef struct s_ray
{
	t_vec3						origin;
	t_vec3						direction;
}								t_ray;

typedef struct s_canvas
{
	unsigned short				width;
	unsigned short				height;
	double						aspect_ratio;
}								t_canvas;

typedef struct s_data
{
	void						*mlx;
	void						*win;
	void						*img;
	char						*addr;
	int							bits_per_pixel;
	int							line_length;
	int							endian;
	t_canvas					view;
	t_world						*world;
}								t_data;

typedef struct s_sp_cal
{
	t_vec3						oc;
	double						a;
	double						half_b;
	double						c;
	double						discr;
	double						root;
}								t_sp_cal;

typedef struct s_cy_cal
{
	t_vec3						oc;
	double						a;
	double						half_b;
	double						c;
	double						discr;
	double						root;
	double						height;
	bool						hit_body;
	bool						hit_caps;
	t_vec3						hit_point;
}								t_cy_cal;

typedef bool	(*t_int_fn)(t_object_list *, t_ray *, t_hit_record *);

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
void			render(t_data *data);
t_vec3			calculate_pixel_color(t_world *world);
t_vec3			ambient_light_on_obj(t_world *world);
t_vec3			diffuse_light_on_obj(t_world *world, t_ray shadow_ray);
bool			hit_plane(t_object_list *obj, t_ray *ray, t_hit_record *rec);
bool			hit_object(t_object_list *obj, t_ray *r, t_hit_record *rec);
bool			hit_sphere(t_object_list *obj, t_ray *r, t_hit_record *rec);
bool			hit_cylinder(t_object_list *obj, t_ray *ray, t_hit_record *rec);

#endif
