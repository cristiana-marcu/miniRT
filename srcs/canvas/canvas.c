/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:15:42 by cmarcu            #+#    #+#             */
/*   Updated: 2021/04/22 16:39:42 by cmarcu           ###   ########.fr       */
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
			canvas.pixel.color[0] = 0;
			canvas.pixel.color[1] = 0;
			canvas.pixel.color[2] = 0;
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
	ca.pixel.color[0] = c[0];
	ca.pixel.color[1] = c[1];
	ca.pixel.color[2] = c[2];
}

typedef struct s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
} t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
