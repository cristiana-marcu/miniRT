/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:36:08 by cmarcu            #+#    #+#             */
/*   Updated: 2021/04/22 16:36:39 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

#include <math.h>
#include "my_math.h"
#include <mlx.h>

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

#endif
