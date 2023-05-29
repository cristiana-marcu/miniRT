/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/29 20:33:51 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	load_cy(t_pars *pars, char **tokens)
{
	t_cylinder	*cy;
	bool		is_right[5];

	cy = malloc(sizeof(t_cylinder));
	bzero(is_right, sizeof(is_right));
	if (tokens == NULL)
		print_err(E_MEM | E_EXIT);
	else if (ft_len_matrix(tokens) != 6)
		pars->errors |= E_CY;
	else
	{
		cy->pos = get_vector(tokens[1], &is_right[0], POINT);
		cy->N = get_vector(tokens[2], &is_right[1], NVEC);
		cy->r = get_dob(tokens[3], &is_right[2], SEGM) / 2;
		cy->H = get_dob(tokens[4], &is_right[3], SEGM);
		cy->color = normalize_color(get_vector(tokens[5], &is_right[4], COLRS));
		if (!check_right(is_right, 5))
			pars->errors |= E_CY;
		else if (add_obj_to_scene(&(pars->world), cy, CYLINDER) == NULL)
			print_err(E_MEM | E_EXIT);
	}
}
