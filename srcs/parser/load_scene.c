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


# include "minirt.h"

void	rm_spaces(char**line)
{
	char *trim_line;
	char *aux;

	aux = ft_strtrim(*line, " ");
	trim_line = ft_strtrim(aux, "\n");
	free(*line);
	if (aux)
		free(aux);
	if (!trim_line)
		print_err(E_MEM | E_EXIT);
	*line = trim_line;
}

bool	check_range_cols(t_vec3 cols)
{
	if (cols.x > 255 || cols.x < 0)
		return (false);
	if (cols.y > 255 || cols.y < 0)
		return (false);
	if (cols.z > 255 || cols.z < 0)
		return (false);
	else
	 	return (true);
}

bool	check_amb(t_ambientLight amb)
{
	if (amb.color.x == -1)
		return (false);
	else if (amb.range > 1 || amb.range < 0)
		return (false);
	else
		return (true);
}

double get_col(char *col)
{
	char *aux;

	aux = col;
	if (ft_strlen(col) < 1 || ft_strlen(col) > 3)
		return (-1);
	while (aux && *aux)
	{
		if (ft_isdigit(*aux))
			aux++;
		else
			return (-1);
	}
	return ((double)ft_atoi(col));
}

t_vec3 get_colours(char *str)
{
	t_vec3	cols;
	char	**rgb;

	rgb = ft_split(str, ',');
	if (rgb == NULL)
		print_err(E_MEM | E_EXIT);
	else if (ft_len_matrix(rgb) != 3)
	{
		ft_free_matrix(rgb);
		return ((t_vec3){-1, -1, -1});
	}
	cols.x = get_col(rgb[0]);
	cols.y = get_col(rgb[1]);
	cols.z = get_col(rgb[2]);
	ft_free_matrix(rgb);
	if (check_range_cols(cols))
		return (cols);
	else
		return ((t_vec3){-1, -1, -1});
}


double	get_bright(char *str)
{
	double	bright;

	if (ft_strlen(str) != 3 || (str[0] != '0' && str[0] != '1'))
		return (-1);
	else if (str[1] != '.' || str[3] != '\0')
		return (-1);
	else if (str[2] < '0' || str[2] > '9')
		return (-1);
	else
	 	bright = ft_atof(str);
	if (bright > 1 || bright < 0)
		return (-1);
	else if (bright == 0 && (str[0] != '0' || str[2] != '0'))
		return (-1);
	return (bright);
}

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

void	load_objs(t_pars *pars)
{
	rm_spaces(&pars->line);
	if (ft_strlen(pars->line) == 0 || \
		(ft_strlen(pars->line) == 1 && *pars->line == '\n'))
		return ;
	if (ft_strncmp(pars->line, "A ", 2) == 0)
	 	load_amb(pars, ft_split(pars->line, ' '));
/*
	else if (ft_strncmp(pars->line, "C ", 2) == 0)
	 	load_cam(pars);
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

void	load_scene(char *scene)
{
	t_pars pars;

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
