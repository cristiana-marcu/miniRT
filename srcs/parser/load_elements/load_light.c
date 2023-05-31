/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/17 11:34:08 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	load_light(t_pars *pars, char **tokens)
{
	t_light	light;
	bool	is_right[3];

	light = (t_light){};
	bzero(is_right, sizeof(is_right));
	if (tokens == NULL)
		print_err(E_MEM | E_EXIT);
	else if (pars->dup[LIT])
		pars->errors |= E_DUP_LIT;
	else if (ft_len_matrix(tokens) != 4)
		pars->errors |= E_LIT;
	else
	{
		pars->dup[LIT] = true;
		light.pos = get_vector(tokens[1], &is_right[0], POINT);
		light.brightness = get_dob(tokens[2], &is_right[1], BRIGHT);
		light.color = get_vector(tokens[3], &is_right[2], COLRS);
		if (check_right(is_right, 3))
		{
			light.color = normalize_color(light.color);
			pars->world.light = light;
		}
		else
			pars->errors |= E_LIT;
	}
}
