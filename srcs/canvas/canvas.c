/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:15:42 by cmarcu            #+#    #+#             */
/*   Updated: 2023/03/11 18:02:34 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/canvas.h"

// t_canvas canvas(unsigned short x, unsigned short y)
// {
// 	t_canvas canvas;
// 	int i;
// 	int j;

// 	canvas.width = x;
// 	canvas.height = y;
// 	i = 0;
// 	j = 0;
// 	while (i < x)
// 	{
// 		while (j < y)
// 		{
// 			canvas.pixel.x = j;
// 			canvas.pixel.y = i;
// 			canvas.pixel.color[0] = 0;
// 			canvas.pixel.color[1] = 0;
// 			canvas.pixel.color[2] = 0;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (canvas);
// }

// void	write_pixel(t_canvas ca, unsigned short x, unsigned short y, t_vec3 c)
// {
// 	ca.pixel.x = x;
// 	ca.pixel.y = y;
// 	ca.pixel.color[0] = c[0];
// 	ca.pixel.color[1] = c[1];
// 	ca.pixel.color[2] = c[2];
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
