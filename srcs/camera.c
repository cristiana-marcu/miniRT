/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:35:29 by cmarcu            #+#    #+#             */
/*   Updated: 2023/04/29 11:26:50 by cmarcu           ###   ########.fr       */
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

t_camera init_camera(t_data *data)
{
	t_camera camera;
	
	/*TODO que venga del parser todo lo hardcodeado*/
	camera.from = vctor(-1, -2, 0);
	camera.HFOV = 110.0;
	camera.lookAt = vctor(-0.5, 0, 1);
	/*_____________________________________________*/
	
	double theta;
	double field_width;

	theta = degree_to_radian(camera.HFOV);
	field_width = 2 * tan(theta / 2);
	camera.viewport_width = field_width;
	camera.viewport_height = field_width / data->view.aspect_ratio;

	camera.w = vec3_normalize(vec3_subs(camera.from, camera.lookAt));
	camera.u = vec3_normalize(vec3_cross(vctor(0, 1, 0), camera.w));
	camera.v = vec3_cross(camera.w, camera.u);

	camera.horizontal = vec3_mult(camera.u, camera.viewport_width);
	camera.vertical = vec3_mult(camera.v, camera.viewport_height);
	camera.lower_left_corner = vec3_subs(vec3_subs(vec3_subs(camera.from, vec3_division(camera.horizontal, 2)), vec3_division(camera.vertical, 2)), camera.w);

	return (camera);
}