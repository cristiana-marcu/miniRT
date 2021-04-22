/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2021/04/22 11:03:47 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/my_math.h"
#include <stdio.h>

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

int main()
{
	t_projectile proj;
	proj.position[0] = 0;
	proj.position[1] = 1;
	proj.position[2] = 0;
	proj.velocity[0] = 1;
	proj.velocity[1] = 1;
	proj.velocity[2] = 0;

	t_environment env;
	env.gravity[0] = 0;
	env.gravity[1] = -0.1;
	env.gravity[2] = 0;
	env.wind[0] = -0.1;
	env.wind[1] = 0;
	env.wind[2] = 0;
	while (proj.position[1] > 0)
	{
		proj = tick(env, proj);
		printf("%f, %f\n", proj.position[0], proj.position[1]);
	}
}
