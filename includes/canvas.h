/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:36:08 by cmarcu            #+#    #+#             */
/*   Updated: 2023/03/11 17:46:56 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

#include <math.h>
#include "vectors.h"
#include "ray.h"
#include <mlx.h>
#include <stdlib.h>

typedef struct s_pixel
{
	unsigned short x;
	unsigned short y;
	t_vec3 color;
} t_pixel;

typedef struct s_canvas
{
	unsigned short width;
	unsigned short height;
	t_pixel pixel;
} t_canvas;

typedef struct s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
} t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
