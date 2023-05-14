/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:21:03 by drontome          #+#    #+#             */
/*   Updated: 2023/05/08 18:31:46 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <mlx.h>
# include "libft.h"
# include "errors.h"
# include "objects.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */


/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_pars
{
	u_int16_t	errors;
	int			fd;
	bool		dup[3];
	char		*line;
	t_world		world;

}			t_pars;


/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */
typedef enum e_may
{
	AMB,
	CAM,
	LIT,
}			t_may;
/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
bool	check_scene(int argc, char **argv);
void 	print_err(uint16_t err);
void	load_scene(char *scene);
void	load_amb(t_pars *pars, char **tokens);
double	get_bright(char *str);
t_vec3 get_colours(char *str);

#endif
