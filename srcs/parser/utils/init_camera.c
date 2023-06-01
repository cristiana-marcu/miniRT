/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:35:29 by cmarcu            #+#    #+#             */
/*   Updated: 2023/06/01 13:22:01 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static double	degree_to_radian(double degree)
{
	return (degree * M_PI / 180);
}

t_camera	init_camera(t_data *data)
{
	t_camera	camera;
	double		theta;
	double		field_width;

	camera.from = data->world->camera.from;
	camera.hfov = data->world->camera.hfov;
	camera.lookat = data->world->camera.lookat;
	theta = degree_to_radian(camera.hfov);
	field_width = 2 * tan(theta / 2);
	camera.viewport_width = field_width;
	camera.viewport_height = field_width / data->view.aspect_ratio;
	camera.w = vec3_negate(camera.lookat);
	camera.u = vec3_norm(vec3_cross(vctor(0, 1, 0), camera.w));
	camera.v = vec3_cross(camera.w, camera.u);
	camera.horizontal = vec3_mult(camera.u, camera.viewport_width);
	camera.vertical = vec3_mult(camera.v, camera.viewport_height);
	camera.lower_left_corner = vec3_subs(vec3_subs(vec3_subs(camera.from, \
	vec3_div(camera.horizontal, 2)), vec3_div(camera.vertical, 2)), camera.w);
	return (camera);
}
