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
	t_light		light;
	bool		is_right[2];

	light = (t_light){};
	bzero(is_right, sizeof(is_right));
	if (tokens == NULL)
		print_err(E_MEM | E_EXIT);
	else if (pars->dup[LIT])
		pars->errors |= E_DUP_LIT;
	else if (ft_len_matrix(tokens) != 3)
		pars->errors |= E_LIT;
	else
	{
		pars->dup[LIT] = true;
		light.pos = get_vector(tokens[1], &is_right[0], POINT);
		light.brightness = get_dob(tokens[2], &is_right[1], BRIGHT);
		if (check_right(is_right, 2))
			pars->world.light = light;
		else
			pars->errors |= E_LIT;
	}
	ft_free_matrix(tokens);
}
