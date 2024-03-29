/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/29 20:05:01 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	is_valid_char(char c);
static bool	no_forb_char(int fd);

bool	check_scene(int argc, char **argv)
{
	int	fd;

	fd = 0;
	if (argc != 2)
		print_err(E_BAD_ARG);
	else if (ft_str_ends_with(argv[1], ".rt"))
		print_err(E_EXTEN);
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			print_err(E_OPEN);
		else if (no_forb_char(fd))
			return (true);
	}
	return (false);
}

static bool	is_valid_char(char c)
{
	if (c == 'A' || c == 'C' || c == 'L')
		return (true);
	else if (c == 's' || c == 'p' || c == 'l' || c == 'c' || c == 'y')
		return (true);
	else if (c == '-' || c == ',' || c == '.')
		return (true);
	else if (c == '\n' || c == ' ' || c == '\t' || c == '#')
		return (true);
	else if (ft_isdigit(c))
		return (true);
	else
		return (false);
}

static bool	no_forb_char(int fd)
{
	char	c;
	int		no_empty;

	c = 0;
	no_empty = read(fd, &c, 1);
	while (is_valid_char(c) && read(fd, &c, 1) > 0)
		continue ;
	close(fd);
	if (!is_valid_char(c) && c != 0)
		print_err(E_CHAR);
	else if (c == 0 && no_empty < 1)
		print_err(E_EMPTY);
	else
		return (true);
	return (false);
}
