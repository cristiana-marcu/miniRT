/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/06/03 12:36:12 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	load_sp(t_pars *pars, char **tokens)
{
	t_sphere	*sp;
	bool		is_right[3];

	sp = malloc(sizeof(t_sphere));
	bzero(is_right, sizeof(is_right));
	if (tokens == NULL)
		print_err(E_MEM | E_EXIT);
	else if (ft_len_matrix(tokens) != 4)
		pars->errors |= E_SP;
	else
	{
		sp->center = get_vector(tokens[1], &is_right[0], POINT);
		sp->r = get_dob(tokens[2], &is_right[1], SEGM) / 2;
		sp->color = normalize_color(get_vector(tokens[3], &is_right[2], COLRS));
		if (!check_right(is_right, 3))
		{
			pars->errors |= E_SP;
			free(sp);
		}
		else if (add_obj_to_scene(&(pars->world), sp, SPHERE) == NULL)
			print_err(E_MEM | E_EXIT);
	}
}
