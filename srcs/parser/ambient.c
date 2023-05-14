/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/14 11:32:25 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "parser.h"

static bool	check_amb(t_ambientLight amb);

void	load_amb(t_pars *pars, char **tokens)
{
	t_ambientLight amb;

	amb = (t_ambientLight){};
	if (tokens == NULL)
		print_err(E_MEM | E_EXIT);
	else if (pars->dup[AMB])
		pars->errors |= E_DUP_AMB;
	else if(ft_len_matrix(tokens) != 3)
		pars->errors |= E_AMB;
	else
	{
		pars->dup[AMB] = true;
		amb.range = get_bright(tokens[1]);
		amb.color = get_colours(tokens[2]);
		if (check_amb(amb))
			pars->world.amb_light = amb;
		else
			pars->errors |= E_AMB;
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


