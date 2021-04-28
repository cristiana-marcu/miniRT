/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: RAMON <RAMON@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2021/04/28 11:14:45 by RAMON            ###   ########.fr       */
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
	
	vec3_add(res.position, proj.position, proj.velocity);
	vec3_add(res.velocity, proj.velocity, env.gravity);
	vec3_add(res.velocity, res.velocity, env.wind);
	return (res);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_projectile proj;
	proj.position[0] = 0;
	proj.position[1] = 1;
	proj.position[2] = 0;
	proj.velocity[0] = 1;
	proj.velocity[1] = 1.8;
	proj.velocity[2] = 0;

	t_environment env;
	env.gravity[0] = 0;
	env.gravity[1] = -0.1;
	env.gravity[2] = 0;
	env.wind[0] = -0.1;
	env.wind[1] = 0;
	env.wind[2] = 0;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 700, 700, "miniRT");
	img.img = mlx_new_image(mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
	vec3_normalize(proj.velocity, proj.velocity);
	vec3_mult(proj.velocity, proj.velocity, 11.25);
	while (proj.position[1] >= 0 && proj.position[0] >= 0)
	{
		proj = tick(env, proj);
		my_mlx_pixel_put(&img, 700 - (int)proj.position[0], 700 - (int)proj.position[1], 0x00FF0000);
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
