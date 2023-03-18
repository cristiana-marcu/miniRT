/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:36:08 by cmarcu            #+#    #+#             */
/*   Updated: 2023/03/18 15:38:50 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

#include <math.h>
#include "vectors.h"
#include "ray.h"
#include <mlx.h>
#include <stdlib.h>

# define K_ESC 53

typedef struct s_canvas
{
	unsigned short width;
	unsigned short height;
	double aspect_ratio;
} t_canvas;

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
	t_canvas view;
} t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
