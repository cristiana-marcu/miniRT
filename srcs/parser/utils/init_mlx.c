/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:39:49 by cmarcu            #+#    #+#             */
/*   Updated: 2023/05/31 22:55:41 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"
#include "objects.h"
#include "parser.h"

static void	finish_rt(t_data *mlx);

int	hook_keydown(int key, t_data *mlx)
{
	if (key == K_ESC)
	{
		finish_rt(mlx);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	close_win(t_data *mlx)
{
	finish_rt(mlx);
	exit(EXIT_SUCCESS);
}

void	init_mlx(t_data	*data)
{
	data->view.aspect_ratio = 16.0 / 9.0;
	data->view.width = 1920;
	data->view.height = (int)(data->view.width / data->view.aspect_ratio);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->view.width, \
		data->view.height, "miniRT");
	data->img = mlx_new_image(data->mlx, data->view.width, data->view.height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
}

void	start_rt(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, hook_keydown, &data->mlx);
	mlx_hook(data->win, 17, 0, close_win, data);
	mlx_loop(data->mlx);
}

static void	finish_rt(t_data *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	free_objs(&mlx->world->objs, free);
	free(mlx->world->rec);
	free(mlx->world);
}
