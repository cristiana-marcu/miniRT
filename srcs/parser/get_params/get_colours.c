/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/14 19:23:31 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "parser.h"

static bool	check_range_cols(t_vec3 cols);
double get_col(char *col);

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

static bool	check_range_cols(t_vec3 cols)
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

