/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_pl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/06/03 12:40:52 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	load_pl(t_pars *pars, char **tokens)
{
	t_plane	*pl;
	bool	is_right[3];

	pl = malloc(sizeof(t_plane));
	bzero(is_right, sizeof(is_right));
	if (tokens == NULL)
		print_err(E_MEM | E_EXIT);
	else if (ft_len_matrix(tokens) != 4)
		pars->errors |= E_PL;
	else
	{
		pl->pos = get_vector(tokens[1], &is_right[0], POINT);
		pl->n = get_vector(tokens[2], &is_right[1], NVEC);
		pl->color = normalize_color(get_vector(tokens[3], &is_right[2], COLRS));
		if (!check_right(is_right, 3))
		{
			pars->errors |= E_PL;
			free(pl);
		}
		else if (add_obj_to_scene(&(pars->world), pl, PLANE) == NULL)
			print_err(E_MEM | E_EXIT);
	}
}
