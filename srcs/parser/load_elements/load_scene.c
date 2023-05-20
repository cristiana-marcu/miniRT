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
static char	**tokenizator(char *line);
static t_world *p_world(t_world old_world);


t_world	*load_scene(char *scene)
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
	{
		free_objs(&(pars.world.objs), free);
		print_err(pars.errors | E_EXIT);
	}
	return (p_world(pars.world));
}

static void	load_objs(t_pars *pars)
{
	char **tokens;
	int	len;

	if (ft_strlen(pars->line) == 0 ||
		(ft_strlen(pars->line) == 1 && *pars->line == '\n'))
		return ;
	tokens = tokenizator(pars->line);
	len = ft_strlen(tokens[0]);
	if (ft_strncmp(tokens[0], "A", len) == 0)
		load_amb(pars, tokens);
	else if (ft_strncmp(tokens[0], "C", len) == 0)
		load_cam(pars, tokens);
	else if (ft_strncmp(tokens[0], "L", len) == 0)
		load_light(pars, tokens);
	else if (ft_strncmp(tokens[0], "sp", len) == 0)
		load_sp(pars, tokens);
	else if (ft_strncmp(tokens[0], "pl", len) == 0)
		load_pl(pars, tokens);
	else if (ft_strncmp(tokens[0], "cy", len) == 0)
		load_cy(pars, tokens);
	else
		pars->errors |= E_ID;
	ft_free_matrix(tokens);
}

static char	**tokenizator(char *line)
{
	char	*trim_line;
	char	**tokens;

	trim_line = ft_strtrim(line, "\n");
	if (!trim_line)
		print_err(E_MEM | E_EXIT);
	tokens = smart_split(trim_line);
	free(trim_line);
	if (!tokens)
		print_err(E_MEM | E_EXIT);
	return (tokens);
}

static t_world *p_world(t_world old_world)
{
	t_world	*world;

	world = malloc(sizeof(t_world));
	if (!world)
		print_err(E_MEM | E_EXIT);
	*world = old_world;
	world->rec = (t_hit_record*)malloc(sizeof(t_hit_record));
	return (world);
}
