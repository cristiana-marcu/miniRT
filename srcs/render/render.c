/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:42:19 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/26 18:50:04 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "ray.h"
#include <stdbool.h>
#include <stdio.h>

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	set_face_normal(t_ray *ray, t_hit_record *rec)
{
	rec->front_face = vec3_dot(ray->direction, rec->n) < 0;
	if (rec->front_face == false)
		rec->n = vec3_negate(rec->n);
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
/**
 * The function renders an image by shooting rays and calculating the color of
 * each pixel.
 *
 * @param data a pointer to a struct that contains information about the scene
 * and the image being rendered.
 */

void	render(t_data *data)
{
	t_vec3	aux;
	t_ray	ray;
	t_vec3	pixel_color;

	aux.y = 0;
	while (aux.y < data->view.height)
	{
		aux.x = 0;
		while (aux.x < data->view.width)
		{
			shoot_ray(data, &ray, &aux);
			pixel_color = ray_color(&ray, data->world);
			my_mlx_pixel_put(data, aux.x, aux.y, vec3_to_rgb(pixel_color));
			aux.x++;
		}
		aux.y++;
	}
}
