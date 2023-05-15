/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/15 17:19:05 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

double	get_crd(char *crd)
{
	int		i;
	bool	is_float;

	i = 0;
	is_float = false;
	if (ft_strlen(crd) < 1 || ft_strlen(col) > 3) //pendiente
		return (-1); //pendiente asignar valor
	while (crd && crd[i])
	{
		if (ft_isdigit(crd[i]))
			i++;
		else if (i == 0 && crd[i] == '-')
			i++;
		else if ((i > 1 || i == 1 && crd[i] == '-') &&\
			crd[i] == '.' && !is_float)
		{
			is_float = true;
			i++;
		}
		else
			return (-1);// pendiente
	}
	if (is_float)
		return ((double)ft_atoi(col));// NOOOO
	return (-1);// pendiente
}

t_vec3	get_view(char *str)
{
	t_vec3 view;
	char **xyz;

	xyz = ft_split(str, ',');
	if (!xyz)
		print_err(E_MEM | E_EXIT);
	else if (ft_len_matrix(xyz) != 3)
	{
		ft_free_matrix(rgb);
		return ((t_vec3){-1, -1, -1}); //pendiente de asignar valor
	}
	view.x = get_crd(xyz[0]);
	view.y = get_crd(xyz[1]);
	view.z = get_crd(xyz[2]);
	ft_free_matrix(xyz);
	if (check_range_view(view))
		return (view);
	else
		return ((t_vec3){-1, -1, -1});//pendiente SIMILAR A get_colours
}

void	load_cam(t_pars *pars, char **tokens)
{
	t_camera	cam;

	cam = (t_camera){};
	if (tokens == NULL)
		print_err(E_MEM | E_EXIT);
	else if (pars->dup[CAM])
		pars->errors |= E_DUP_CAM;
	else if (ft_len_matrix(tokens) != 4)
		pars->errors |= E_CAM;
	else
	{
		pars->dup[CAM] = true;
		cam.from = get_view(tokens[1]);
		cam.lookAt = get_nvec(tokens[2]);
		cam.HFOV = get_fov(tokens[3]);
		if (check_cam(cam))
			pars->world.camera = cam;
		else
			pars->errors |= E_CAM;
	}
	ft_free_matrix(tokens);
}

static bool	check_amb(t_ambientLight amb)
{
	if (amb.color.x == -1)
		return (false);
	else if (amb.range > 1 || amb.range < 0)
		return (false);
	else
		return (true);
}
