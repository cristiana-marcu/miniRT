/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/29 20:23:31 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	get_crd(char *crd, double *c);

bool	check_right(bool *is_right, int size)
{
	while (size-- > 0)
	{
		if (!is_right[size])
			return (false);
	}
	return (true);
}

double	get_dob(char *str, bool *is_right, t_range r)
{
	double	f;
	char	*p;

	p = str;
	f = ft_strtod(str, &p);
	if (*p != '\0')
		*is_right = false;
	else
		*is_right = check_rg(&f, r);
	return (f);
}

t_vec3	get_vector(char *str, bool *is_right, t_range r)
{
	t_vec3	vec;
	char	**xyz;

	vec = (t_vec3){};
	xyz = ft_split(str, ',');
	if (!xyz)
		print_err(E_MEM | E_EXIT);
	else if (ft_len_matrix(xyz) != 3)
	{
		ft_free_matrix(xyz);
		return (vec);
	}
	if (get_crd(xyz[0], &vec.x) && get_crd(xyz[1], &vec.y) \
		&& get_crd(xyz[2], &vec.z))
		*is_right = check_rg(&vec, r);
	ft_free_matrix(xyz);
	return (vec);
}

t_vec3	normalize_color(t_vec3 color)
{
	t_vec3	normalized_color;

	normalized_color.x = color.x / 255;
	normalized_color.y = color.y / 255;
	normalized_color.z = color.z / 255;
	return (normalized_color);
}

static bool	get_crd(char *crd, double *c)
{
	char	*p;

	p = crd;
	if (ft_strlen(crd) < 1 || ft_strlen(crd) > 1000)
		return (false);
	*c = ft_strtod(crd, &p);
	if (*p != '\0')
		return (false);
	else
		return (true);
}
