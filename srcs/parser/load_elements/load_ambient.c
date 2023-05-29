/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ambient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/29 20:16:27 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	load_amb(t_pars *pars, char **tokens)
{
	t_ambientLight	amb;
	bool			is_right[2];

	amb = (t_ambientLight){};
	if (tokens == NULL)
		print_err(E_MEM | E_EXIT);
	else if (pars->dup[AMB])
		pars->errors |= E_DUP_AMB;
	else if (ft_len_matrix(tokens) != 3)
		pars->errors |= E_AMB;
	else
	{
		pars->dup[AMB] = true;
		amb.range = get_dob(tokens[1], &is_right[0], BRIGHT);
		amb.color = get_vector(tokens[2], &is_right[1], COLRS);
		if (check_right(is_right, 2))
		{
			amb.color = normalize_color(amb.color);
			pars->world.amb_light = amb;
		}
		else
			pars->errors |= E_AMB;
	}
}
