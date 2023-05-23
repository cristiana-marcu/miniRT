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
		cam.from = get_vector(tokens[1], &is_right[0], POINT);
		cam.lookAt = get_vector(tokens[2], &is_right[1], NVEC);
		cam.HFOV = get_dob(tokens[3], &is_right[2], HFOV);
		if (cam.HFOV == 180)
			cam.HFOV = 179.99;
		if (check_right(is_right, 3))
			pars->world.camera = cam;
		else
			pars->errors |= E_CAM;
	}
}
