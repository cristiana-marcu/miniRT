/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:15:42 by cmarcu            #+#    #+#             */
/*   Updated: 2022/07/11 18:56:24 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/canvas.h"

t_canvas canvas(unsigned short x, unsigned short y)
{
	t_canvas canvas;
	int i;
	int j;

	canvas.width = x;
	canvas.height = y;
	i = 0;
	j = 0;
	while (i < x)
	{
		while (j < y)
		{
			canvas.pixel.x = j;
			canvas.pixel.y = i;
			canvas.pixel.color.x = 0;
			canvas.pixel.color.y = 0;
			canvas.pixel.color.z = 0;
			j++;
		}
		i++;
	}
	return (canvas);
}

void	write_pixel(t_canvas ca, unsigned short x, unsigned short y, t_vec3 c)
{
	ca.pixel.x = x;
	ca.pixel.y = y;
	ca.pixel.color.x = c.x;
	ca.pixel.color.y = c.y;
	ca.pixel.color.z = c.z;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
