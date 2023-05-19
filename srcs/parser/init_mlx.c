/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/18 18:08:54 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include "canvas.h"
#include "objects.h"

int	hook_keydown(int key, t_data *mlx)
{
	if (key == K_ESC)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	close_win(t_data *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	exit(0);
}

void init_mlx(t_data	*data)
{
	data->view.aspect_ratio = 16.0 / 9.0;
	data->view.width = 1080;
	data->view.height = (int)(data->view.width / data->view.aspect_ratio);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->view.width, data->view.height, "miniRT");
	data->img = mlx_new_image(data->mlx, data->view.width, data->view.height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
		&data->endian);
}

void	start_rt(t_data *data)
{
	mlx_put_image_to_window(data->mlx,data->win, data->img, 0, 0);
	mlx_key_hook(data->win, hook_keydown, &data->mlx);
	mlx_hook(data->win, 17, 0, close_win, data);
	mlx_loop(data->mlx);
}
