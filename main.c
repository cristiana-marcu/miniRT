/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2021/04/28 11:14:45 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_math.h"
#include "canvas.h"
#include <stdio.h>
#include <mlx.h>

typedef struct s_projectile
{
	t_vec3	position;
	t_vec3	velocity;
} t_projectile;

typedef struct s_environment
{
	t_vec3	gravity;
	t_vec3	wind;
} t_environment;

t_projectile tick(t_environment env, t_projectile proj)
{
	t_projectile res;
	
	res.position = vec3_add(proj.position, proj.velocity);
	res.velocity = vec3_add(proj.velocity, env.gravity);
	res.velocity = vec3_add(res.velocity, env.wind);
	return (res);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_projectile proj;
	proj.position.x = 0;
	proj.position.y = 1;
	proj.position.z = 0;
	proj.velocity.x = 1;
	proj.velocity.y = 1.8;
	proj.velocity.z = 0;

	t_environment env;
	env.gravity.x = 0;
	env.gravity.y = -0.1;
	env.gravity.z = 0;
	env.wind.x = -0.1;
	env.wind.y = 0;
	env.wind.z = 0;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 700, 700, "miniRT");
	img.img = mlx_new_image(mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
	proj.velocity = vec3_normalize(proj.velocity);
	proj.velocity = vec3_mult(proj.velocity, 11.25);
	while (proj.position.y >= 0 && proj.position.x >= 0)
	{
		proj = tick(env, proj);
		my_mlx_pixel_put(&img, 700 - (int)proj.position.x, 700 - (int)proj.position.y, 0x00FF0000);
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
