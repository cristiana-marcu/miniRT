/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/17 10:47:18 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_right(bool *is_right, int size)
{
	while (size-- > 0)
	{
		if (!is_right[size])
			return (false);
	}
	return (true);
}

void	load_cam(t_pars *pars, char **tokens)
{
	t_camera	cam;
	bool		is_right[3];

	cam = (t_camera){};
	bzero(is_right, sizeof(is_right));
	if (tokens == NULL)
		print_err(E_MEM | E_EXIT);
	else if (pars->dup[CAM])
		pars->errors |= E_DUP_CAM;
	else if (ft_len_matrix(tokens) != 4)
		pars->errors |= E_CAM;
	else
	{
		pars->dup[CAM] = true;
		cam.from = get_view(tokens[1], &is_right[0], VIEW);
		cam.lookAt = get_view(tokens[2], &is_right[1], NVEC);
		cam.HFOV = get_fov(tokens[3], &is_right[2], HFOV);
		if (check_right(is_right, 3))
			pars->world.camera = cam;
		else
			pars->errors |= E_CAM;
	}
	ft_free_matrix(tokens);
}
