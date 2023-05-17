/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/17 11:11:31 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	check_rg(void *data, t_range r);

bool	get_crd(char *crd, double *c)
{
	char	*p;

	p = crd;
	if (ft_strlen(crd) < 1 || ft_strlen(crd) > 1000) //TODO
		return (false);
	*c = ft_strtod(crd, &p);
	if (*p != '\0') // TODO
		return (false);
	else
		return (true);
}

double	get_fov(char *str, bool *is_right, t_range HFOV)
{
	double	f;
	char	*p;

	p = str;
	f = ft_strtod(str, &p);
	if (*p != '\0') // TODO
		*is_right = false;
	else
		*is_right = check_rg(&f, HFOV);
	return (f);
}

t_vec3	get_view(char *str, bool *is_right, t_range r)
{
	t_vec3	view;
	char	**xyz;

	view = (t_vec3){};
	xyz = ft_split(str, ',');
	if (!xyz)
		print_err(E_MEM | E_EXIT);
	else if (ft_len_matrix(xyz) != 3)
	{
		ft_free_matrix(xyz);
		return (view);
	}
	if (get_crd(xyz[0], &view.x) && get_crd(xyz[1], &view.y) \
		&& get_crd(xyz[2], &view.z))
		*is_right = check_rg(&view, r);
	ft_free_matrix(xyz);
	return (view);
}

static bool	check_rg(void *data, t_range r)
{
	t_vec3	*v;
	double	*f;

	if (r == HFOV)
		f = (double *)data;
	else
		v = (t_vec3 *)data;
	if (r == HFOV && (*f > 180 || *f < 0))
		return (false);
	else if (r == VIEW && (v->x > INT_MAX || v->y > INT_MAX || v->z > INT_MAX))
		//TODO
		return (false);
	else if (r == VIEW && (v->x < INT_MIN || v->y < INT_MIN || v->z < INT_MIN))
		//TODO
		return (false);
	else if (r == NVEC && (v->x > 1 || v->y > 1 || v->z > 1))
		return (false);
	else if (r == NVEC && (v->x < 0 || v->y < 0 || v->z < 0))
		return (false);
	return (true);
}
