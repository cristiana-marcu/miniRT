/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:35:29 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/30 11:41:07 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdbool.h>
#include <stdio.h>
#include "objects.h"
#include "canvas.h"

double	degree_to_radian(double degree)
{
	return (degree * M_PI / 180);
}

/**
 * The function initializes a camera struct with given parameters and calculates its properties.
 *
 * @param data It is a pointer to a struct that contains information about the scene being rendered,
 * such as the world, the view, and the image.
 *
 * @return The function `init_camera` is returning a `t_camera` structure.
*/

t_camera	init_camera(t_data *data)
{
	t_camera	camera;
	double		theta;
	double		field_width;

	/*TODO que venga del parser todo lo hardcodeado*/

	camera.from = data->world->camera.from ;
	camera.HFOV = data->world->camera.HFOV;
	camera.lookAt = data->world->camera.lookAt;
//	camera.from = vctor(0, 0.5, 2);
//	camera.HFOV = 80.0;
//	camera.lookAt = vctor(0, 0, -1);

	/*_____________________________________________*/
	theta = degree_to_radian(camera.HFOV);
	field_width = 2 * tan(theta / 2);
	camera.viewport_width = field_width;
	camera.viewport_height = field_width / data->view.aspect_ratio;
	camera.w = vec3_negate(camera.lookAt);
	camera.u = vec3_norm(vec3_cross(vctor(0, 1, 0), camera.w));
	camera.v = vec3_cross(camera.w, camera.u);
	camera.horizontal = vec3_mult(camera.u, camera.viewport_width);
	camera.vertical = vec3_mult(camera.v, camera.viewport_height);
	camera.lower_left_corner = vec3_subs(vec3_subs(vec3_subs(camera.from, vec3_div(camera.horizontal, 2)), vec3_div(camera.vertical, 2)), camera.w);
	return (camera);
}
