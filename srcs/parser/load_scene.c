/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/13 18:20:04 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	load_objs(t_pars *pars);
static void	rm_spaces(char **line);

void	load_scene(char *scene)
{
	t_pars	pars;

	pars = (t_pars){};
	pars.fd = open(scene, O_RDONLY);
	if (pars.fd < 0)
		print_err(E_OPEN | E_EXIT);
	pars.line = get_next_line(pars.fd);
	while (pars.line != NULL)
	{
		load_objs(&pars);
		free(pars.line);
		pars.line = get_next_line(pars.fd);
	}
	if (pars.errors != 0)
		print_err(pars.errors);
}

static void	load_objs(t_pars *pars)
{
	rm_spaces(&pars->line);
	if (ft_strlen(pars->line) == 0 ||
		(ft_strlen(pars->line) == 1 && *pars->line == '\n'))
		return ;
	if (ft_strncmp(pars->line, "A ", 2) == 0)
		load_amb(pars, ft_split(pars->line, ' '));
	/*
	else if (ft_strncmp(pars->line, "C ", 2) == 0)
		load_cam(pars, ft_split(pars->line, ' '));
	else if (ft_strncmp(pars->line, "L ", 2) == 0)
			load_light(pars);
	else if (ft_strncmp(pars->line, "sp ", 3) == 0)
			load_sp(pars);
	else if (ft_strncmp(pars->line, "pl ", 3) == 0)
			load_pl(pars);
	else if (ft_strncmp(pars->line, "cy ", 3) == 0)
			load_cy(pars);
*/
	else
		pars->errors |= E_ID;
}

static void	rm_spaces(char **line)
{
	char	*trim_line;
	char	*aux;

	aux = ft_strtrim(*line, " ");
	trim_line = ft_strtrim(aux, "\n");
	free(*line);
	if (aux)
		free(aux);
	if (!trim_line)
		print_err(E_MEM | E_EXIT);
	*line = trim_line;
}
