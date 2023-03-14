/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2023/03/14 18:55:56 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"
#include <stdio.h>
#include <mlx.h>

int	hook_keydown(int key, t_data *mlx)
{
	if (key == K_ESC)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	close()
{
	exit(0);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 720;
	const int image_height = (int)(image_width / aspect_ratio);

	double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

	t_vec3 origin = vctor(0, 0, 0);
    t_vec3 horizontal = vctor(viewport_width, 0, 0);
    t_vec3 vertical = vctor(0, viewport_height, 0);
    t_vec3 lower_left_corner = vec3_subs(vec3_subs(origin, vec3_division(horizontal, 2)), vec3_subs(vec3_division(vertical, 2), vctor(0, 0, focal_length)));

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, image_width, image_height, "miniRT");
	img.img = mlx_new_image(mlx, image_width, image_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
	for (int j = image_height-1; j >= 0; --j) {
         for (int i = 0; i < image_width; ++i) {
            double u = (double)i / (image_width-1);
            double v = (double)j / (image_height-1);
            t_ray r = rctor(origin, vec3_add(vec3_add(lower_left_corner, vec3_mult(horizontal, u)), vec3_subs(vec3_mult(vertical, v), origin)));
            t_vec3 pixel_color = ray_color(&r);
			my_mlx_pixel_put(&img, i, j, vec3_toInt(pixel_color)*1000);
        }
    }
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_key_hook(mlx_win, hook_keydown, mlx);
	mlx_hook(mlx_win, 17, 0, close, NULL);
	mlx_loop(mlx);
}
